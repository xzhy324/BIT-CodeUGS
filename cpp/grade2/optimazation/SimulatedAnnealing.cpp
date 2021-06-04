#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAX_SIZE=100;//工件和机器数量的最大值
const int InstanceNum = 11;//用例个数
FILE* fp;

const double end_temperature = 1e-3;//T的最终冷却温度
const double temperature_factor = 0.9999;//以等比方式降温的比例系数
const double start_temperature = 1e8;//T的起始温度
const double deltaFactor = 1;//value函数中用于减少接受坏解的概率，这个因子越大，则回退坏解的概率会越低
const int max_markov_length = 2000000;//控制markov链的长度
const bool youhua_rollback = true;


int n,m;//n个工件，m个车间
int c[MAX_SIZE][MAX_SIZE];//第i个零件在第j个车间的加工时间
int p[MAX_SIZE];//排列的形式刻画解

int CalculateTime();
double schedule(int outerLoop,double T);
void initP(int* P);
void reassignP(int* P);
double value(int time);
void getData();
void intcpy(int* dst,const int* src);
template <class T>
void swap(const T& a,const T& b){T tmp=a;a=b;b=tmp;}


/*————————————————————————MAIN————————————————————————————————————————*/
int main(){

    //将结果保存到statistics.txt************************************************************
    int totalResult=0;
    FILE *output = fopen("statistics.txt","a+");
    fseek(output,0,SEEK_END);fputc('\n',output);//定位到文件末尾的新起一行
    fprintf(output,"/***********************************************/\n");
    fprintf(output,"racial:%lf\nstart :%lf\nend   :%lf\nrollback?:%d\n\n"
            ,temperature_factor,start_temperature,end_temperature,youhua_rollback);
    //将结果保存到statistics.txt************************************************************

    fp= fopen("flowshop-test-10-student.txt","r");
    if(!fp){
        cout<<"Error when opening file!";
        exit(0);
    }

    for(int insNum=0;insNum<InstanceNum;insNum++){

        int gbest = 0x3f3f3f3f;

        //读入本例的所需数据
        getData();

        //随机生成一个初始解p[]，初始化温度,并计算初始解的完成时间
        initP(p);
        double T = start_temperature;
        int currentTime = CalculateTime();

        //开始迭代
        for(int t=1; ;t++){

            gbest = min(gbest,currentTime);//记忆化搜索

            //温度随迭代轮次下降
            T = schedule(t,T);
            if(T<=end_temperature || t>=max_markov_length){
                printf("Instance:%2d Result:%d Rounds:%d gbest:%d\n",insNum,currentTime,t,gbest);

                //将结果打印到statistics.txt
                fprintf(output,"Instance:%d Result:%d Rounds:%d\n",insNum,currentTime,t);
                totalResult+=currentTime;

                break;
            }

            //重新生成一个排列p
            int p_tmp[MAX_SIZE];
            intcpy(p_tmp,p);
            reassignP(p);
            //对于新的排列p，计算下一时间
            int nextTime = CalculateTime();

            double deltaT = value(nextTime) - value(currentTime);
            if(deltaT < 0)//更新更好的
                currentTime = nextTime;
            else{//依概率回退不好的
                double possibility = exp(-deltaT / T);
                if( rand()%int(1.0e5) /1.0e5 <= possibility ){
                    currentTime = nextTime;
                }else{//未接受最坏解，则本次应该回退
                    if(youhua_rollback)
                        intcpy(p,p_tmp);
                }
            }
        }

    }

    //将结果打印到statistics.txt**********************************************
    fprintf(output,"\nThe total result is:%d\n",totalResult);
    fprintf(output,"The total time is:%g\n",(double)clock() /CLOCKS_PER_SEC);
    fprintf(output,"/***********************************************/\n");
    fclose(output);
    //将结果打印到statistics.txt**********************************************

    printf("The total time is: %.4g s\n",(double)clock() /CLOCKS_PER_SEC);
    fclose(fp);
    return 0;
}
/*————————————————————————MAIN————————————————————————————————————————*/


int CalculateTime(){//通过引入辅助矩阵s来记录开始时间，并按照尽可能紧凑的方式来
    int s[MAX_SIZE][MAX_SIZE];//第i个零件在第j车间加工的开始时间，用于辅助刻画最后的完成时间

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

void getData(){
    char line[4*MAX_SIZE];
    fgets(line,4*MAX_SIZE,fp);fgets(line,4*MAX_SIZE,fp);//开头的乱七八糟的加号和用例编号不需要
    fscanf(fp,"%d %d", &n, &m);
    for(int i=0;i<n;i++)
        for(int j=0;j<2*m;j++)//编号项舍弃，只读入数据项
            fscanf(fp,"%d",&c[i][j/2]);

    fgets(line,4*MAX_SIZE,fp);
}

void intcpy(int *dst,const int *src){
    for(int i=0;i<n;i++)
        dst[i]=src[i];
}