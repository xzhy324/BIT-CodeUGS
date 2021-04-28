#include "iostream"
using namespace std;
const int N=1005, INF=0x3f3f3f3f, NE=20005;
struct Edge{
    int u,v,w;//u-v<=w
}edge[NE];
int n,ml,md,edge_n;
int dis[N];

int bellman_ford(int source_v){
    for(int i=1;i<=n;i++)dis[i]=INF;
    dis[source_v]=0;
    for(int i=1;i<=n-1;i++){
        for(int j=1;j<=edge_n;j++){
            if(dis[edge[j].v] > dis[edge[j].u] + edge[j].w ){
                dis[edge[j].v] = dis[edge[j].u] + edge[j].w;
            }
        }
    }
    for(int i=1;i<=edge_n;i++){
        if( dis[edge[i].v] > dis[edge[i].u] + edge[i].w)
            return false;
    }
    return true;
}

int main(){
    cin>>n>>ml>>md;
    edge_n=1;
    dis[1]=0;
    for(int i=2;i<=n;i++)dis[i]=INF;


    for(int i=1;i<=ml;i++){
        scanf("%d %d %d",&edge[edge_n].u,&edge[edge_n].v,&edge[edge_n].w);
        edge_n++;
    }
    for(int i=ml+1;i<=ml+md;i++){
        scanf("%d %d %d",&edge[edge_n].v,&edge[edge_n].u,&edge[edge_n].w);
        edge[edge_n].w = 0 - edge[edge_n].w;
        edge_n++;
    }
    for(int i=1;i<=n-1;i++){//相邻的约束条件
        edge[edge_n].u=i+1;
        edge[edge_n].v=i;
        edge[edge_n].w=0;
        edge_n++;
    }
    edge_n--;

    if(bellman_ford(1) ){
        if(dis[n]==INF)cout<<"-2"<<endl;
        else cout<<dis[n]<<endl;
    }else cout<<"-1"<<endl;
    return 0;
}