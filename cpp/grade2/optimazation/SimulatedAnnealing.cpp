#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_SIZE=100;
const int InstanceNum = 10;

const double Epsilon = 1e-5;//T的最终冷却温度
const double temperature_factor = 1 - 1e-4;//降温速度
const double start_temperature = 1e8;//起始温度
const double deltaFactor = 1;

int n,m;//n个工件，m个车间
int s[MAX_SIZE][MAX_SIZE];//第i个零件在第j车间加工的开始时间
int c[MAX_SIZE][MAX_SIZE];//第i个零件在第j个车间的加工时间
int p[MAX_SIZE];//排列的形式刻画解
int CalculateTime();
double schedule(int outerLoop,double T);
void initP(int* P);
void reassignP(int* P);
double value(int time);
template <class T>
void swap(const T& a,const T& b){
    T tmp=a;a=b;b=tmp;
}
int main(){
    for(int insNum=1;insNum<=InstanceNum;insNum++){
        //读入本例的所需数据
        cin>>n>>m;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                cin>>c[i][j];

        //随机生成一个初始解p[]，初始化温度,并计算初始解的完成时间
        initP(p);
        double T = start_temperature;
        int currentTime = CalculateTime();

        //开始迭代
        for(int t=1; ;t++){
            //温度随迭代轮次下降
            T = schedule(t,T);
            if(T<Epsilon){
                cout<<"The result is "<<currentTime<<" ,the total cal is "<<t<<endl;
                break;
            }

            //重新生成一个排列p
            reassignP(p);

            int nextTime = CalculateTime();

            double deltaT = value(nextTime) - value(currentTime);
            if(deltaT < 0)//更新更好的
                currentTime = nextTime;
            else{//依概率回退不好的
                double possibility = exp(-deltaT / T);
                if( rand()%int(1.0e5) /1.0e5 <= possibility ){
                    currentTime = nextTime;
                }else{
                    
                }
            }
        }

    }
}

int CalculateTime(){
    //cout<<"calculating!\n";
    s[p[0]][0] = 0;
    for(int i=1;i<m;i++)
        s[p[0]][i] = s[p[0]][i-1] + c[p[0]][i-1];

    for(int i=1;i<n;i++){
        s[p[i]][0] = s[p[i-1]][0] + c[p[i-1]][0];
        for(int j=1;j<m;j++)
            s[p[i]][j] = max(s[p[i-1]][j] + c[p[i-1]][j], s[p[i]][j-1] + c[p[i]][j-1]);
    }

    return s[p[n-1]][m-1] + c[p[n-1]][m-1];
}

double schedule(int outerLoop,double T){
    return T * temperature_factor;
}

void initP(int* P){
    for(int i=0;i<n;i++)
        P[i]=i;
    random_shuffle(P,P+n);
}

void reassignP(int *P){
    int a = rand()%n;
    int b = rand()%n;
    while(a==b)
        b = rand()%n;
    swap(P[a],P[b]);
}

double value(int time){
    return time * deltaFactor;
}