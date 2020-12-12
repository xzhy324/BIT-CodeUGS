#include "iostream"
#include "algorithm"
#define N 1020
struct VexSetNode{
    int set;
}vex[N];
struct EdgeSetNode{
    int head,tail;
    int weight;
}edge[N];
int cmp(const void *p1, const void *p2){return (*(EdgeSetNode*)p1).weight>(*(EdgeSetNode*)p2).weight?1:-1;}
int main(){
    for(int i=1;i<N;i++)vex[i].set=i;
    int n,m;scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y,w;scanf("%d %d %d",&x,&y,&w);
        edge[i-1].head=x;
        edge[i-1].tail=y;
        edge[i-1].weight=w;
    }
    /*******/
    qsort(edge,m,sizeof(edge[1]),cmp);
    int edgeNum=0,vexNum=0;
    //int cost=0;
    while(vexNum<=n-2&&edgeNum<=m-1){
        int vset1=vex[edge[edgeNum].tail].set;
        int vset2=vex[edge[edgeNum].head].set;
        if(vset1!=vset2){
            vexNum++;
            for(int i=1;i<=n;i++){
                if(vex[i].set==vset1)vex[i].set=vset2;
            }
            //cost+=edge[edgeNum].weight;
        }
        edgeNum++;
    }
    /*********/
    int mark=1;
    for(int i=2;i<=n&&mark;i++)if(vex[i].set!=vex[i-1].set)mark=0;//judge if unconected
    if(mark==1)printf("%d\n",cost);
    else printf("-1\n");
    return 0;
}