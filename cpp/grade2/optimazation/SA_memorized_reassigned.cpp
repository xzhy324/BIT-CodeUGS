#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

/*---------------------可调整参数区--------------------------------------------------*/
const double start_temperature = 1e8;//T的起始温度
const double end_temperature = 1e-3;//T的最终冷却温度
const double temperature_factor = 0.9999;//以等比方式降温的比例系数
const double deltaFactor = 1;//value函数中用于减少接受坏解的概率，这个因子越大，则回退坏解的概率会越低
const int max_markov_length = 200000;//控制markov链的长度

const bool memorized_search = true;//是否启用记忆化搜索
const int reassigned_round = 10;//每次重新生成排列的个数
/*--------------------------------------------------------------------------------*/

const int MAX_SIZE=100;//工件和机器数量的最大值
const int InstanceNum = 11;//用例个数
int n,m;//n个工件，m个车间
int c[MAX_SIZE][MAX_SIZE];//第i个零件在第j个车间的加工时间
int p[MAX_SIZE];//排列的形式刻画解
FILE* fp;//数据输入文件指针
FILE *output;//统计数据输出文件指针

int CalculateTime();//对于给定排列计算时间
double schedule(int outerLoop,double T);//退火降温函数
void initP(int* P);//初始化随机排列的函数
void reassignP(int* P);//生成新排列的函数
double value(int time);//评估当前解质量的函数
void getData();//数据读入函数
void intcpy(int* dst,const int* src);//用于排列之间的复制
void output_initialize();
void output_close(int totalResult);

/*————————————————————————MAIN————————————————————————————————————————*/
int main(){
    output_initialize();//打开统计文件，并将参数保存到statistics.txt

    fp= fopen("flowshop-test-10-student.txt","r");//输入文件的读取
    if(!fp){
        std::cout<<"Error when opening file!";
        exit(0);
    }

    int totalResult=0;//记录所有用例总和，用于粗略估计解质情况
    for(int insNum=0;insNum<InstanceNum;insNum++){
        getData();//读入本例的所需数据

        initP(p);//随机初始化排列P
        double T = start_temperature;//初始化温度
        int currentTime = CalculateTime();//初始化并计算初始解的完成时间
        int gbest = currentTime;//初始化全局最优解

        //开始迭代退火
        for(int t=1; ;t++){
            gbest = std::min(gbest,currentTime);//记忆全局最优质
            T = schedule(t,T);//温度随迭代轮次下降
            if(T<=end_temperature || t>=max_markov_length){//边界条件判断
                printf("Instance:%2d Result:%d Rounds:%d gbest:%d\n",insNum,currentTime,t,gbest);
                //将结果打印到statistics.txt
                if(memorized_search){
                    fprintf(output,"Instance:%d Result:%d Rounds:%d\n",insNum,gbest,t);
                }else{
                    fprintf(output,"Instance:%d Result:%d Rounds:%d\n",insNum,currentTime,t);
                }
                totalResult+=currentTime;
                break;
            }//边界条件判断结束


            int p_old[MAX_SIZE],p_new_min[MAX_SIZE];
            intcpy(p_old,p);//p_old内记录着上一次排列结果，不应再改变
            int nextTime=0x3f3f3f3f;
            for(int i=1;i<=reassigned_round;i++){//重新生成一个排列p
                intcpy(p,p_old);
                reassignP(p);
                int t_tmp = CalculateTime();//对于新的排列p，计算下一时间
                if(nextTime>t_tmp){//t_tmp更优则更新
                    nextTime = t_tmp;
                    intcpy(p_new_min,p);
                }
            }
            intcpy(p,p_new_min);//此时p是搜索的新解中最小的排列

            double deltaT = value(nextTime) - value(currentTime);
            if(deltaT < 0){//更新更好的
                currentTime = nextTime;
            }else{//依概率回退不好的
                double possibility = exp(-deltaT / T);
                if( rand()%int(1.0e5) /1.0e5 <= possibility ){
                    currentTime = nextTime;
                }else{//未接受最坏解，则本次应该回退
                    intcpy(p,p_old);
                }
            }//结束节点更新
        }//结束迭代退火

    }

    output_close(totalResult);//将结果打印到statistics.txt
    printf("The total time is: %.4g s\n",(double)clock() /CLOCKS_PER_SEC);
    fclose(fp);
    return 0;
}
/*————————————————————————MAIN————————————————————————————————————————*/

/*-----------------------REALIZATION----------------------------------*/
int CalculateTime(){//通过引入辅助矩阵s来记录开始时间，并按照尽可能紧凑的方式来
    int s[MAX_SIZE][MAX_SIZE];//第i个零件在第j车间加工的开始时间，用于辅助刻画最后的完成时间

    s[p[0]][0] = 0;
    for(int i=1;i<m;i++)
        s[p[0]][i] = s[p[0]][i-1] + c[p[0]][i-1];

    for(int i=1;i<n;i++){
        s[p[i]][0] = s[p[i-1]][0] + c[p[i-1]][0];
        for(int j=1;j<m;j++)
            s[p[i]][j] = std::max(s[p[i-1]][j] + c[p[i-1]][j], s[p[i]][j-1] + c[p[i]][j-1]);
    }

    return s[p[n-1]][m-1] + c[p[n-1]][m-1];
}

double schedule(int outerLoop,double T){
    return T * temperature_factor;
}

void initP(int* P){
    for(int i=0;i<n;i++)
        P[i]=i;
    std::random_shuffle(P,P+n);
}

void reassignP(int *P){
    int a = rand()%n;
    int b = rand()%n;
    while(a==b)
        b = rand()%n;
    std::swap(P[a],P[b]);
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

void output_initialize(){
    output = fopen("statistics.txt","a+");
    fseek(output,0,SEEK_END);fputc('\n',output);//定位到文件末尾的新起一行
    fprintf(output,"/***********************************************/\n");
    fprintf(output,"racial:%lf\nstart :%lf\nend   :%lf\nmarkov :%d\nreassigned_round:%d\nmemorized_search:\n\n"
            ,temperature_factor,start_temperature,end_temperature,max_markov_length,reassigned_round,memorized_search);
}

void output_close(int totalResult){
    fprintf(output,"\nThe total result is:%d\n",totalResult);
    fprintf(output,"The total time is:%g\n",(double)clock() /CLOCKS_PER_SEC);
    fprintf(output,"/***********************************************/\n");
    fclose(output);
}
/*-----------------------REALIZATION----------------------------------*/