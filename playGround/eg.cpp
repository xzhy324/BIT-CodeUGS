
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cuda_runtime.h>
#include <math_functions.h>
#include <cmath>
#include <ctime>
using namespace std;

void CheckCudaReturnCode(cudaError_t code, const char *fileName, int lineNo)
{
	if(code == cudaSuccess) return;
	cerr << "Cuda call failed at " << fileName << ":" << lineNo 
		<< " " << cudaGetErrorString(code) << endl;
	exit(-1);
}

#define CK(x) CheckCudaReturnCode((x), __FILE__, __LINE__)

// 为了简单，只支持一个BLOCK
#define TIDX (threadIdx.x)
#define TCNT (blockDim.x)
#define CEIL(x,y) (((x) + (y) - 1)/(y))
__device__ inline size_t t_range_size(size_t s)
{
	return CEIL(s, TCNT);
}
__device__ inline size_t t_range_start(size_t s)
{
	return t_range_size(s) * TIDX;
}
__device__ inline size_t t_range_end(size_t s)
{
	size_t tmp = t_range_size(s) * (TIDX + 1);
	return tmp > s ? s : tmp;
}

bool InitCUDA()
{
	int count;
	cudaGetDeviceCount(&count);
	if(count == 0) {
		cerr << "There is no cuda device" << endl;
		return false;
	}
	cout << "Toal " << count << " cuda devices" << endl;

	int i;
	for(i = 0;i < count;i++) {
		cudaDeviceProp prop;
		if(cudaGetDeviceProperties(&prop, i) == cudaSuccess) {
			if(prop.major >= 1) {
				break;
			}
		}
	}

	if(i == count) {
		cerr << "There is no device supporting CUDA 1.x" << endl;
		return false;
	}

	cudaSetDevice(i);
	return true;
}

// http://www.cnblogs.com/yeahgis/archive/2012/07/13/2590485.html
// 高斯分布的随机数，均值为0，方差为1
double gaussrand()
{
    static double V1, V2, S;
    static int phase = 0;
    double X;
     
    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;
             
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);
         
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
         
    phase = 1 - phase;
 
    return X;
}

#define ALIGN_FLOAT(x) (((x) + 3) & (~3))

template<size_t ROW, size_t COL>
struct Matrix
{
	const static int row = ROW;
	const static int col = COL;
	float data[ROW][ALIGN_FLOAT(COL)];
	__device__ __host__ inline float* operator[](size_t x)
	{
		//assert(x < ROW);
		return data[x];
	}
};

template<size_t ROW, size_t COL>
ostream& operator<<(ostream& out, Matrix<ROW,COL>& w)
{
	out << "[(" << w.row << " x " << w.col << ")" << endl;
	for(int i = 0;i < w.row;i++) {
		out << "\t[";
		for(int j = 0;j < w.col;j++) {
			if(j > 0) out << ",";
			out << w[i][j];
		}
		out << "]" << endl;
	}
	out << "]";
	return out;
}

template<size_t SIZE>
struct Vector
{
	const static int size = SIZE;
	float data[SIZE];
	__device__ __host__ inline float &operator[](size_t x)
	{
		//assert(x < SIZE);
		return data[x];
	}
};

template<size_t SIZE>
ostream& operator<<(ostream& out, Vector<SIZE>& v)
{
	out << "[(" << v.size << ") ";
	for(int i = 0;i < v.size;i++) {
		if(i > 0) out << ",";
		out << v[i];
	}
	out << "]";
	return out;
}

// 矩阵乘法
template<size_t ROW, size_t COL>
__device__ inline void mul(Matrix<ROW,COL> &w, Vector<COL> &x, Vector<ROW> &out)
{
	/*
	for(int i = 0;i < w.row;i++) {
		out[i] = 0;
		for(int j = 0;j < w.col;j++) {
			out[i] += w[i][j] * x[j];
		}
	}
	*/
	// 把x加载到shared中，然后进行计算
	extern __shared__ float shared[];
	for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
		shared[i] = x[i];
	}
	__syncthreads();
	for(int i = t_range_start(w.row); i < t_range_end(w.row); i++) {
		float t = 0;
		for(int j = 0;j < w.col;j++) {
			t += w[i][j] * shared[j];
		}
		out[i] = t;
	}
	__syncthreads();
}

// w转置，然后和v相乘
template<size_t ROW, size_t COL>
__device__ inline void t_and_mul(Matrix<ROW, COL> &w, Vector<ROW> &v, Vector<COL> &out)
{
	/*
	for(int i = 0;i < w.col;i++) {
		out[i] = 0;
		for(int j = 0;j < w.row;j++) {
			out[i] += w[j][i] * v[j];
		}
	}
	*/
	extern __shared__ float shared[];
	for(int i = t_range_start(v.size); i < t_range_end(v.size); i++) {
		shared[i] = v[i];
	}
	__syncthreads();
	for(int i = t_range_start(w.col); i < t_range_end(w.col); i++) {
		float t = 0;
		for(int j = 0;j < w.row;j++) {
			t += w[j][i] * shared[j];
		}
		out[i] = t;
	}
	__syncthreads();
}

template<size_t SIZE>
__device__ inline void add(Vector<SIZE> &x, Vector<SIZE> &y, Vector<SIZE> &out)
{
	/*
	for(int i = 0;i < x.size;i++) {
		out[i] = x[i] + y[i];
	}
	*/
	for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
		out[i] = x[i] + y[i];
	}
	__syncthreads();
}

template<size_t SIZE>
__device__ inline void sub(Vector<SIZE> &x, Vector<SIZE> &y, Vector<SIZE> &out)
{
	/*
	for(int i = 0;i < x.size;i++) {
		out[i] = x[i] - y[i];
	}
	*/
	for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
		out[i] = x[i] - y[i];
	}
	__syncthreads();
}

template<size_t SIZE>
__device__ inline void mul(float x, Vector<SIZE> &y, Vector<SIZE> &out)
{
	/*
	for(int i = 0;i < y.size;i++) {
		out[i] = x * y[i];
	}
	*/
	for(int i = t_range_start(y.size); i < t_range_end(y.size); i++) {
		out[i] = x * y[i];
	}
	__syncthreads();
}

template<size_t SIZE>
__device__ inline void mul(Vector<SIZE> &x, float y, Vector<SIZE> &out)
{
	mul(y, x, out);
}

template<size_t SIZE>
__device__ inline void copy(Vector<SIZE> &x, Vector<SIZE> &out)
{
	/*
	for(int i = 0;i < x.size;i++) {
		out[i] = x[i];
	}
	*/
	for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
		out[i] = x[i];
	}
	__syncthreads();
}

__device__ inline float sum_of_shared(int size)
{
	extern __shared__ float shared[];

	__syncthreads();

	// 0 thread进行求和
	if(TIDX == 0) {
		for(int i = 1;i < size;i++) {
			shared[0] += shared[i];
		}
	}
	__syncthreads();

	float ret = shared[0];

	__syncthreads();

	return ret;
}

__device__ inline float max_of_shared(int size)
{
	extern __shared__ float shared[];

	__syncthreads();

	if(TIDX == 0) {
		for(int i = 1;i < size;i++) {
			if(shared[0] < shared[i]) {
				shared[0] = shared[i];
			}
		}
	}
	__syncthreads();

	float ret = shared[0];

	__syncthreads();

	return ret;
}


template<size_t SIZE>
__device__ inline float max(Vector<SIZE>& x)
{
	assert(x.size > 0);

	extern __shared__ float shared[];

	if(TIDX < x.size) {
		shared[TIDX] = x[TIDX];
	}

	for(int i = t_range_start(x.size) + 1; i < t_range_end(x.size); i++) {
		if(shared[TIDX] < x[i]) {
			shared[TIDX] = x[i];
		}
	}

	return max_of_shared(min(TCNT, x.size));
}

template<size_t SIZE>
__device__ inline float sum(Vector<SIZE>& x)
{
	assert(x.size > 0);

	extern __shared__ float shared[];

	if(TIDX < x.size) {
		shared[TIDX] = 0;
	}

	for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
		shared[TIDX] += x[i];
	}

	return sum_of_shared(min(TCNT, x.size));
}

template<size_t SIZE>
struct Softmax
{
	__device__ static inline float calc(Vector<SIZE>& x, Vector<SIZE>& y)
	{
		// - \sum y_j * log( exp(x_j) / \sum exp(x_k) )
		/*
		  log( exp(x_j) / \sum exp(x_k) )
		= x_j - log \sum exp(x_k)
		= x_j - (max + log \sum exp(x_k - max))
		*/

		float maxX = max(x);

		/*
		float xSum = 0;
		for(int i = 0;i < x.size;i++) {
			xSum += expf(x[i] - maxX);
		}
		*/

		extern __shared__ float shared[];
		if(TIDX < x.size) {
			shared[TIDX] = 0;
		}

		for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
			shared[TIDX] += expf(x[i] - maxX);
		}

		float xSum = sum_of_shared(min(TCNT, x.size));

		/*
		float ret = 0;
		for(int i = 0;i < x.size;i++) {
			ret += y[i] * (x[i] - (maxX + logf(xSum)));
		}
		*/
		if(TIDX < x.size) {
			shared[TIDX] = 0;
		}
		for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
			shared[i] += y[i] * (x[i] - (maxX + logf(xSum)));
		}

		float ret = sum_of_shared(min(TCNT, x.size));

		return -ret;
	}


	static inline float calc_host(Vector<SIZE>& x, Vector<SIZE>& y)
	{
		// - \sum y_j * log( exp(x_j) / \sum exp(x_k) )
		/*
		  log( exp(x_j) / \sum exp(x_k) )
		= x_j - log \sum exp(x_k)
		= x_j - (max + log \sum exp(x_k - max))
		*/

		float maxX = x[0];
		for(int i = 1;i < x.size;i++) {
			if(x[i] > maxX) {
				maxX = x[i];
			}
		}

		float xSum = 0;
		for(int i = 0;i < x.size;i++) {
			xSum += expf(x[i] - maxX);
		}

		float ret = 0;
		for(int i = 0;i < x.size;i++) {
			ret += y[i] * (x[i] - (maxX + logf(xSum)));
		}

		return -ret;
	}

	__device__ static inline void propagate_delta(Vector<SIZE> &x, Vector<SIZE> &y, Vector<SIZE> &out)
	{
		/*
		  - d \sum y_j * log( exp(x_j) / \sum exp(x_k) )
		= - d \sum y_j * x_j - d \sum y_j log (\sum exp(x_k) )
		= - y_i + \sum (y_j * exp(x_i) / \sum exp(x_k))
		= - y_i + exp(x_i) (\sum y_j) / (\sum exp(x_k))
		*/

		float maxX = max(x);

		// -y + exp(x) sum_of_y / sum_of_exp(x)

		/*
		float sumOfY = 0;
		float sumOfX = 0;
		
		for(int i = 0;i < x.size;i++) {
			out[i] = expf(x[i] - maxX);
			sumOfY += y[i];
			sumOfX += out[i];
		}
		*/

		for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
			out[i] = expf(x[i] - maxX);
		}

		float sumOfY = sum(y);
		float sumOfX = sum(out);

		float t = sumOfY/sumOfX;

		mul(t, out, out);
		sub(out, y, out);
	}
};

template<size_t SIZE>
struct Relu
{
	__device__ __host__ static inline float forward(float v)
	{
		return v >= 0 ? v : 0;
	}

	__device__ __host__ static inline float derive(float v)
	{
		return v >= 0 ? 1 : 0;
	}

	__device__ static inline void forward(Vector<SIZE> &x, Vector<SIZE> &out)
	{
		/*
		for(int i = 0;i < x.size;i++) {
			out[i] = x[i] >= 0 ? x[i] : 0;
		}
		*/
		for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
			out[i] = x[i] >= 0 ? x[i] : 0;
		}
		__syncthreads();
	}

	__device__ static inline void derive(Vector<SIZE> &x, Vector<SIZE> &out)
	{
		/*
		for(int i = 0;i < x.size;i++) {
			out[i] = x[i] >= 0 ? 1 : 0;
		}
		*/
		for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
			out[i] = x[i] >= 0 ? 1 : 0;
		}
		__syncthreads();
	}

	__device__ static inline void derive_and_dot_into(Vector<SIZE> &x, Vector<SIZE> &out)
	{
		// out = dot(dx, out)
		/*
		for(int i = 0;i < x.size;i++) {
			out[i] = out[i] * (x[i] >= 0 ? 1 : 0);
		}
		*/
		for(int i = t_range_start(x.size); i < t_range_end(x.size); i++) {
			out[i] = out[i] * (x[i] >= 0 ? 1 : 0);
		}
		__syncthreads();
	}
};

// NN的一层
// 1. 输入不算一层
// 2. 层的w矩阵是从前面一层到当前层的w，和NG的定义有些出入
// 3. 层的b是前面一层到当前层的b，和NG的定义有些出入
template <size_t IN_SIZE, size_t OUT_SIZE, typename Activator=Relu<OUT_SIZE> >
struct Layer
{
	typedef Activator ActivatorType;

	// 上一层的输出的个数，不包括bias
	const static int inSize = IN_SIZE;
	// 当前层的输出
	const static int outSize = OUT_SIZE;

	Matrix<OUT_SIZE, IN_SIZE> w;
	Vector<OUT_SIZE> b;
	// 最后一次forward计算之后保存的激活值
	Vector<OUT_SIZE> a;
	//Vector<OUT_SIZE> z;
	// 最后一次反向传播计算之后保存的delta值
	Vector<OUT_SIZE> delta;

	void initWeights()
	{
		for(int i = 0;i < w.row;i++) {
			for(int j = 0;j < w.col;j++) {
				w[i][j] = float(gaussrand() * 0.01);
			}
		}
		for(int i = 0;i < b.size;i++) {
			b[i] = float(gaussrand() * 0.01);
		}
	}

	Layer()
	{
		initWeights();
	}

	__device__ inline void calc(Vector<IN_SIZE> &in)
	{
		// w * in + b
		/*
		mul(w, in, z);
		add(z, b, z);
		Activator::forward(z, a);
		*/

		__shared__ float shared[IN_SIZE];

		// load in
		for(int i = t_range_start(in.size); i < t_range_end(in.size); i++) {
			shared[i] = in[i];
		}

		__syncthreads();

		for(int i = t_range_start(w.row); i < t_range_end(w.row); i++) {
			float t = 0;
			for(int j = 0;j < w.col;j++) {
				t += w[i][j] * shared[j];//in[j];
			}
			t += b[i];
			//z[i] = t;
			a[i] = Activator::forward(t);
		}

		__syncthreads();
	}

	__device__ inline void propagate_delta(Vector<IN_SIZE> &out)
	{
		t_and_mul(w, delta, out);
	}

	// alpha是学习率
	// prevA是上一层的输出
	__device__ inline void update_parameters(float alpha, Vector <IN_SIZE> &prevA)
	{
		// b = b - alpha * delta
		for(int i = t_range_start(b.size); i < t_range_end(b.size); i++) {
			b[i] = b[i] - alpha * delta[i];
		}

		/*
		for(int i = 0;i < w.row;i++) {
			for(int j = 0;j < w.col;j++) {
				w[i][j] = w[i][j] - alpha * prevA[j] * delta[i];
			}
		}
		*/

		/*
		int wSize = w.row * w.col;
		for(int i = TIDX;i < wSize;i += TCNT)
		{
			int x = i / w.col;
			int y = i % w.col;

			w[x][y] = w[x][y] - alpha * prevA[y] * delta[x];
		}
		/*/

		extern __shared__ float shared[];
		if(w.row > w.col) {
			// load prevA
			for(int i = t_range_start(prevA.size); i < t_range_end(prevA.size); i++) {
				shared[i] = prevA[i];
			}
			__syncthreads();

			for(int i = t_range_start(w.row); i < t_range_end(w.row); i++) {
				float t = delta[i];
				for(int j = 0;j < w.col;j++) {
					w[i][j] = w[i][j] - alpha * shared[j]/*prevA[j]*/ * t;//delta[i];
				}
			}
		} else {
			// load delta
			for(int i = t_range_start(delta.size); i < t_range_end(delta.size); i++) {
				shared[i] = delta[i];
			}
			__syncthreads();

			for(int j = t_range_start(w.col); j < t_range_end(w.col); j++) {
				float t = prevA[j];
				for(int i = 0;i < w.row;i++) {
					w[i][j] = w[i][j] - alpha * t * shared[i];//delta[i];
				}
			}
		}
		//*/

		__syncthreads();
	}
};

// model
#define INPUT_SIZE (28 * 28)
#define OUTPUT_SIZE 10
#define MID_SIZE 128
//128
//256
//100

typedef Layer<INPUT_SIZE, MID_SIZE, Relu<MID_SIZE> > L1_TYPE;

typedef Layer<MID_SIZE, OUTPUT_SIZE, Relu<OUTPUT_SIZE> > L2_TYPE;

#define LN_TYPE L2_TYPE
#define LN L2

__global__ void forward(
	L1_TYPE &L1, L2_TYPE &L2,
	Vector<INPUT_SIZE> &input, Vector<OUTPUT_SIZE> &output)
{
	L1.calc(input);

	//L2.calc(L1.a);

	//copy(L2.a, output);
}

template<typename CostFun>
__global__ void backward(
	L1_TYPE &L1, L2_TYPE &L2,
	Vector<INPUT_SIZE> &input, Vector<OUTPUT_SIZE> &y, float alpha)
{
	return;
	// 最后一层
	CostFun::propagate_delta(LN.a, y, LN.delta);
	LN_TYPE::ActivatorType::derive_and_dot_into(LN.a, LN.delta);

	// 其它层
	L2.propagate_delta(L1.delta);
	L1_TYPE::ActivatorType::derive_and_dot_into(L1.a, L1.delta);

	// 更新所有的w和b
	L1.update_parameters(alpha, input);
	L2.update_parameters(alpha, L1.a);
}

// 读取一个整数
int MsbInt(char buf[], int len=4)
{
	int base = 1;
	int ret = 0;
	for(int i = len - 1;i >= 0;i--) {
		ret += (unsigned char)buf[i] * base;
		base *= 256;
	}
	return ret;
}

vector<int> ReadMnistLabels(string fileName)
{
	vector<int> ret;
	ifstream ifs(fileName.c_str(), ios::binary);
	char buf[1000];

	// MAGIC
	ifs.read(buf, 4);
	int magic = MsbInt(buf);
	if(magic != 0x00000801) {
		cerr << "incorrect label file magic number" << endl;
	}

	// num of images
	ifs.read(buf, 4);
	int nImages = MsbInt(buf);

	while(nImages--) {
		ret.push_back(ifs.get());
	}

	return ret;
}

Vector<INPUT_SIZE> * ReadMnistData(string fileName)
{
	ifstream ifs(fileName.c_str(), ios::binary);
	char buf[1000];

	// MAGIC
	ifs.read(buf, 4);
	int magic = MsbInt(buf);
	if(magic != 0x00000803) {
		cerr << "incorrect data file magic number" << endl;
	}

	// num of images
	ifs.read(buf, 4);
	int nImages = MsbInt(buf);
	Vector<INPUT_SIZE> * ret = new Vector<INPUT_SIZE>[nImages];

	int row, col;
	ifs.read(buf, 4);
	row = MsbInt(buf);
	ifs.read(buf, 4);
	col = MsbInt(buf);
	if(row * col != INPUT_SIZE) {
		cerr << "incorrect image size" << endl;
	}

	for(int k = 0;k < nImages;k++) {
		Vector<INPUT_SIZE> &image = ret[k];
		for(int i = 0;i < row * col;i++) {
			image[i] = ifs.get() / 256.0; // 归一化
		}
	}

	return ret;
}

Vector<OUTPUT_SIZE>* translateLabels(vector<int> &labels, int k=10)
{
	int n = labels.size();
	Vector<OUTPUT_SIZE> * ret = new Vector<OUTPUT_SIZE>[n];

	for(int i = 0;i < labels.size();i++) {
		Vector<OUTPUT_SIZE> &tmp = ret[i];
		memset(&tmp, 0, sizeof(tmp));
		assert(labels[i] >= 0 && labels[i] < k);
		tmp[labels[i]] = 1;
	}
	return ret;
}

int getMaxIdx(Vector<OUTPUT_SIZE>& x)
{
	int maxIdx = 0;
	float maxV = x[0];
	for(int i = 0;i < x.size;i++) {
		if(x[i] > maxV) {
			maxV = x[i];
			maxIdx = i;
		}
	}
	return maxIdx;
}

template <typename T>
void CUDA_ALLOC_AND_COPY(T *&to, T *from, size_t size)
{
	CK(cudaMalloc((void**)&to, size));
	CK(cudaMemcpy(to, from, size, cudaMemcpyHostToDevice));
}

int main()
{
	srand(1000);

	if(!InitCUDA()) {
		return -1;
	}

	L1_TYPE *tmpL1 = new L1_TYPE(), *L1;
	CUDA_ALLOC_AND_COPY(L1, tmpL1, sizeof(*L1));
	//delete tmpL1;

	L2_TYPE *tmpL2 = new L2_TYPE(), *L2;
	CUDA_ALLOC_AND_COPY(L2, tmpL2, sizeof(*L2));
	//delete tmpL2;

	cout << "Loading data" << endl;

	// 读取数据
	vector<int> trainLabels = ReadMnistLabels("mnist/train-labels-idx1-ubyte");
	int nTrain = trainLabels.size();
	Vector<OUTPUT_SIZE>* trainLabels2 = translateLabels(trainLabels);
	Vector<OUTPUT_SIZE>* trainLabels2OnGpu;
	CUDA_ALLOC_AND_COPY(trainLabels2OnGpu, trainLabels2, sizeof(trainLabels2[0]) * nTrain);

	Vector<INPUT_SIZE>* trainData = ReadMnistData("mnist/train-images-idx3-ubyte");
	Vector<INPUT_SIZE>* trainDataOnGpu;
	CUDA_ALLOC_AND_COPY(trainDataOnGpu, trainData, sizeof(trainData[0]) * nTrain);

	vector<int> testLabels = ReadMnistLabels("mnist/t10k-labels-idx1-ubyte");
	int nTest = testLabels.size();

	Vector<INPUT_SIZE>* testData = ReadMnistData("mnist/t10k-images-idx3-ubyte");
	Vector<INPUT_SIZE>* testDataOnGpu;
	CUDA_ALLOC_AND_COPY(testDataOnGpu, testData, sizeof(testData[0]) * nTest);

	int M = nTrain;
	int T = nTest;

	typedef Softmax<OUTPUT_SIZE> CostFun;

	// 开始训练
	cout << "Start training" << endl;
	clock_t fullStartedAt = clock();

	Vector<OUTPUT_SIZE> *outputOnCuda;
	CK(cudaMalloc((void**)&outputOnCuda, sizeof(*outputOnCuda)));

	Vector<OUTPUT_SIZE> output;

	// 为了简单，只支持一个BLOCK
	#define N_BLOCK 1
	// 可以多个THREAD
	#define N_THREAD 1024
	#define SHARED_SIZE ((int)sizeof(float) * max(\
		N_THREAD, max(\
			INPUT_SIZE, max(\
				MID_SIZE, max(\
					OUTPUT_SIZE, 0\
		)))))

	for(int step = 0;step < 100000;step++) {
		clock_t step_1 = clock();

		float avgError = 0;

		// 下面这个循环中的forward和backward即使什么都不做，也需要0.75s左右的时间，-_-!
		for(int i = 0;i < M;i++) {
			Vector<INPUT_SIZE> &x = trainDataOnGpu[i];
			Vector<OUTPUT_SIZE> &y = trainLabels2OnGpu[i];

			forward<<<N_BLOCK, N_THREAD, SHARED_SIZE>>>(*L1, *L2, x, *outputOnCuda);

			CK(cudaMemcpy(&output, outputOnCuda, sizeof(output), cudaMemcpyDeviceToHost));

			Vector<OUTPUT_SIZE> &hostY = trainLabels2[i];
			float error = CostFun::calc_host(output, hostY);
			avgError += error;
			//cout << output << " " << hostY << endl;

			backward<CostFun><<<N_BLOCK, N_THREAD, SHARED_SIZE>>>(*L1, *L2, x, y, 0.001);
		}
		avgError /= M;

		clock_t step_2 = clock();

		cout << "step=" << step << " time_cost=" << (step_2 - step_1)*1.0/CLOCKS_PER_SEC << " avgErr=" << avgError << " ";

		// validate
		int nTotal = 0;
		int nGood = 0;
		for(int i = 0;i < M;i++) {
			Vector<INPUT_SIZE> &x = trainDataOnGpu[i];

			forward<<<N_BLOCK, N_THREAD, SHARED_SIZE>>>(*L1, *L2, x, *outputOnCuda);

			CK(cudaMemcpy(&output, outputOnCuda, sizeof(output), cudaMemcpyDeviceToHost));

			int maxIdx = getMaxIdx(output);
			if(maxIdx == trainLabels[i]) {
				nGood++;
			}
			nTotal++;
		}
		cout << "train_accuracy " << nGood << "/" << nTotal << "=" << nGood*1.0/nTotal << " ";
		bool doBreak = false;
		if(nGood * 1.0 / nTotal > 0.95) {
			doBreak = true;
		}

		// check
		nTotal = 0;
		nGood = 0;
		for(int i = 0;i < T;i++) {
			Vector<INPUT_SIZE> &x = testDataOnGpu[i];

			forward<<<N_BLOCK, N_THREAD, SHARED_SIZE>>>(*L1, *L2, x, *outputOnCuda);

			CK(cudaMemcpy(&output, outputOnCuda, sizeof(output), cudaMemcpyDeviceToHost));

			int maxIdx = getMaxIdx(output);
			if(maxIdx == testLabels[i]) {
				nGood++;
			}
			nTotal++;
		}
		cout << "test_accuracy " << nGood << "/" << nTotal << "=" << nGood*1.0/nTotal << " ";

		clock_t step_3 = clock();
		cout << "total_time=" << (step_3-step_1)*1.0/CLOCKS_PER_SEC << endl;
		if(doBreak) {
			break;
		}
	}

	clock_t fullEndedAt = clock();
	cout << "Total cost " << (fullEndedAt - fullStartedAt)/CLOCKS_PER_SEC << " seconds" << endl;

	return 0;
}


