#include "iostream"
#include "fstream"
#include "vector"
#include "cassert"
#include "cstring"

using namespace std;


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