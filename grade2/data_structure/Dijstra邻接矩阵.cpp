#include "iostream"
#define N 30
#define INF 0x3f3f3f3f
int G[N][N],dis[N];
int n,e,origin;
struct Set{
    int node[N];
    int vexNum;
}T;
void init(){
    for(int i=0;i<N;i++)for(int j=0;j<N;j++)G[i][j]=INF;
    for(int i=0;i<N;i++)dis[i]=INF;
}
int min(int a,int b){return a<b?a:b;}
int findMin(){
    int minID=0;
    for(int i=0;i<=n-1;i++){
        bool inTheNodeLine=false;
        for(int j=0;j<=T.vexNum-1&&!inTheNodeLine;j++)if(T.node[j]==i)inTheNodeLine=true;
        if(!inTheNodeLine&&dis[i]>0)minID=i;
    }//保证minID非源点
    for(int i=0;i<=n-1;i++){
        bool inTheNodeLine=false;
        for(int j=0;j<=T.vexNum-1&&!inTheNodeLine;j++)if(T.node[j]==i)inTheNodeLine=true;
        if(!inTheNodeLine&&dis[i]>0&&dis[i]<dis[minID])minID=i;
    }
    return minID;
}
int main(){
    init();
    scanf("%d,%d,%c\n",&n,&e,&origin);
    origin-='a';
    for(int i=1;i<=e;i++){
        int node1,node2,w;
        scanf("<%c,%c,%d>\n",&node1,&node2,&w);
        node1-='a';
        node2-='a';
        G[node1][node2]=w;
    }
    dis[origin]=0;
    for(int i=0;i<=n-1;i++)if(i!=origin&&G[origin][i]!=INF)dis[i]=G[origin][i];
    T.node[0]=origin;
    T.vexNum=1;
    while(T.vexNum<n){
        int minDis=findMin();
        T.node[T.vexNum]=minDis;
        T.vexNum++;
        for(int i=0;i<=n-1;i++){
            if(dis[i]!=0&&G[minDis][i]!=INF)
                dis[i]=min(dis[i],dis[minDis]+G[minDis][i]);
        }
    }
    for(int i=0;i<=n-1;i++)printf("%c:%d\n",i+'a',dis[i]);
    return 0;
}