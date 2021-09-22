#include "cstdio"
#include "cstdlib"
#include "queue"
#define N 1000
using namespace std;
struct ArcNode{
    int adjVex;
    ArcNode *_next;
};
struct VexNode{
    char data;
    ArcNode* FirstArc;//倒序插入
}VexSet[N];
bool visited[N];
queue<VexNode> BFSList;
char ans[N];
char ansPoint;
void init(){
    for(int i=0;i<N;i++)visited[i]=false;
    ansPoint=0;
}
void InsertArc(int start,int end){
    ArcNode* tmp = VexSet[start].FirstArc;
    VexSet[start].FirstArc=(ArcNode*)malloc(sizeof(ArcNode));
    VexSet[start].FirstArc->adjVex=end;
    VexSet[start].FirstArc->_next=tmp;
}
void PrintGraph(int n){
    printf("the ALGraph is\n");
    for(int i=0;i<=n-1;i++){
        printf("%c",VexSet[i].data);
        ArcNode* p=VexSet[i].FirstArc;
        while(p){
            printf(" %d",p->adjVex);
            p=p->_next;
        }
        printf("\n");
    }
}
void BFS(int start){
    visited[start]=true;
    ans[ansPoint++]=VexSet[start].data;
    BFSList.push(VexSet[start]);
    while (!BFSList.empty())
    {
        VexNode CurNode=BFSList.front();
        BFSList.pop();
        ArcNode* p=CurNode.FirstArc;
        while(p!=nullptr){
            if(!visited[p->adjVex]){
                visited[p->adjVex]= true;
                BFSList.push(VexSet[p->adjVex]);
                ans[ansPoint++]=VexSet[p->adjVex].data;
            }
            p=p->_next;
        }
    }
    return;
}
int main(){
    init();
    char c;int VCount=0;
    while((c=getchar())!='*'){
        if(c=='\n')continue;
        VexSet[VCount].data=c;
        VexSet[VCount].FirstArc=nullptr;
        VCount++;
    }
    int head,tail;
    scanf("%d,%d",&head,&tail);
    while(!(head==-1&&tail==-1)){
        InsertArc(head,tail);
        InsertArc(tail,head);
        scanf("%d,%d",&head,&tail);
    }
    PrintGraph(VCount);
    for(int i=0;i<=VCount-1;i++)
        if(!visited[i])BFS(i);
    ans[ansPoint]=0;
    printf("the Breadth-First-Seacrh list:%s\n",ans);
    return 0;
}