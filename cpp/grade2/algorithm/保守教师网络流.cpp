#include "iostream"
#include "queue"
#include "string"
#include "cstring"
using namespace std;
const int N = 505;
const int INF = 0x3f3f3f3f;
struct student{
    int height = 0;
    string sex,music,sport;
}s[N];

int n;
int cap[N][N];//用来记录容量
int flow[N][N];//用来记录最大流
int pre[N];//记录当前的最大流的路径，以便于反向扩充流
int add[N];//记录当前可以增加的流的最大值（到第i个点为止，故而，add【end】就是一次搜索出的可增广容量）

int Edmonds_Karp(int start,int end)//求最大流
{
    int maxflow=0;
    memset(flow,0,sizeof(flow));
    memset(pre,0,sizeof(pre));
    queue<int> q;
    while(true)//每次循环都重新走一遍剩余网络
    {
        memset(add,0,sizeof(add));
        add[start]=INF;//初始的流量是一个无穷大的值
        q.push(start);
        while(!q.empty()) //BFS寻找增广路
        {
            int u=q.front();q.pop();
            for(int v=1;v<=end;v++)
                if(add[v]==0&&cap[u][v]-flow[u][v]>0)//若点v的增广流为0（等价于没有被访问到）， 且（u，v）在残余网络上是可通的。
                {
                    add[v]=min(add[u],cap[u][v]-flow[u][v]);//从源点到u的可增广流量以及u到v的可增广容量取较小的
                    //记录v的父亲，并加入队列中
                    pre[v]=u;
                    q.push(v);
                }
        }
        if(add[end]==0) return maxflow;//无法继续更新最大流量，则当前流已经是最大流
        for(int u=end;u!=start;u=pre[u])//从汇点往回走
        {
            flow[pre[u]][u]+=add[end];//更新正向流
            flow[u][pre[u]]-=add[end];//更新反向流
        }
        maxflow+=add[end]; //更新从s流出的总流量
    }
}

void inputAndBuildNet(){
    memset(cap,0,sizeof (cap));
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>> s[i].height >> s[i].sex >> s[i].music >> s[i].sport;
    for(int i=1;i<=n-1;i++)
        for(int j=i+1;j<=n;j++)
            if(
                    s[i].sex!=s[j].sex
                    && s[i].music==s[j].music
                    && abs(s[i].height-s[j].height)<=40
                    && s[i].sport!=s[j].sport
                    ){
                cap[i][j]=1;
                cap[j][i]=1;
            }

    for(int i=1;i<=n;i++){
        if(s[i].sex=="M"){
            cap[0][i]=1;
            cap[i][n+1]=0;
        }else{
            cap[i][n+1]=1;
            cap[0][i]=0;
        }
    }
}

int main(){
    int T;cin>>T;
    while(T--){
        inputAndBuildNet();
        cout<<n-Edmonds_Karp(0,n+1)<<endl;
    }
    return 0;
}