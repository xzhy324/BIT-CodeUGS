#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "queue"
#define N 30000
using namespace std;
struct BiTree{
    char data;
    BiTree *lp,*rp;
};
queue<BiTree*>line;
void PrintLayer(BiTree *Tree){//bfs queue to visit by layer
    line.push(Tree);
    while(!line.empty()){
        BiTree* curT=line.front(); line.pop();
        printf("%c",curT->data);
        if(curT->lp!=NULL)line.push(curT->lp);
        if(curT->rp!=NULL)line.push(curT->rp);
    }
}
void CrtBT(BiTree *T,char ino[],char post[],int ino_point,int post_point,int cur_N){//cur_N is the current length of ino or post
    if(cur_N==0)T=NULL;
    else{
        int mid_point=-1;//mid_elem in the INO_string
        for(int i=0;i<=cur_N-1;i++){
            if(ino[ino_point+i]!=post[post_point+i]){
                mid_point=i;
                break;
            }
        }

        if(ino[ino_point+cur_N-1]==post[post_point+cur_N-1])mid_point=cur_N-1;//no_right_child's elem pair will always match
        if(mid_point==-1){
            T=NULL;
            return;
        }
        T->data=ino[ino_point+mid_point];

        int left_N=mid_point;
        int right_N=cur_N-left_N-1;
        int left_ip=ino_point;
        int left_pp=post_point;
        int right_ip=ino_point+mid_point+1;
        int right_pp=post_point+left_N;

        if(left_N==0&&right_N==0){
            T->lp=NULL;
            T->rp=NULL;
            return;
        }else if(left_N==0){
            T->lp=NULL;
            T->rp=(BiTree*)malloc(sizeof(BiTree));
            CrtBT(T->rp,ino,post,right_ip,right_pp,right_N);
        }else if(right_N==0){
            T->lp=(BiTree*)malloc(sizeof(BiTree));
            T->rp=NULL;
            CrtBT(T->lp,ino,post,left_ip,left_pp,left_N);
        }else{
            T->lp=(BiTree*)malloc(sizeof(BiTree));
            T->rp=(BiTree*)malloc(sizeof(BiTree));
            CrtBT(T->rp,ino,post,right_ip,right_pp,right_N);
            CrtBT(T->lp,ino,post,left_ip,left_pp,left_N);
        }
    }
    return;
}
int main(){
    char ino[N],post[N];
    scanf("%s %s",ino,post);
    BiTree* T=(BiTree*)malloc(sizeof(BiTree));
    CrtBT(T,ino,post,0,0,strlen(ino));
    PrintLayer(T);
    printf("\n");
    return 0;
}