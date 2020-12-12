#include "stdio.h"
#define maxn 110
typedef struct{
    int x,y;
    int e;
}Triple;
typedef struct{
    Triple data[maxn];
    int mu,nu,tu;//行数，列数，以及非零元个数
    int rpos[maxn];//每行首非零元在data域序号,为0表示该行全为零
}TSMatrix;
TSMatrix M,N,Q;
void input(){
    scanf("%d %d %d",&M.mu,&M.nu,&M.tu);
    for(int i=1;i<=M.tu;i++){
        scanf("%d %d %d",&M.data[i].x,&M.data[i].y,&M.data[i].e);
    }
    scanf("%d %d %d",&N.mu,&N.nu,&N.tu);
    for(int i=1;i<=N.tu;i++){
        scanf("%d %d %d",&N.data[i].x,&N.data[i].y,&N.data[i].e);
    }
}
void output(TSMatrix X){
    printf("%d\n%d\n%d\n",X.mu,X.nu,X.tu);
    for(int i=1;i<=X.tu;i++){
        printf("%d,%d,%d\n",X.data[i].x,X.data[i].y,X.data[i].e);
    }
    /*printf("\n");
    for(int i=1;i<=X.data[X.tu].x;i++){
        printf("rpos%d : %d\n",i,X.rpos[i]);
    }
    printf("\n");*/
}
void initRPOS(TSMatrix *X){//计算每行首非零元的位置
    for(int i=0;i<maxn;i++) X->rpos[i]=0;
    X->rpos[X->data[1].x]=1;
    for(int i=2;i<=X->tu;i++){
        if(X->data[i].x!=X->data[i-1].x){//当行号出现变化的时候记录
            X->rpos[X->data[i].x]=i;
        }
    }
}
void multiply(){
    Q.mu=M.mu;Q.nu=N.nu;Q.tu=0;//q.tu与q.data待定
    for(int m_row=1;m_row<=Q.mu;m_row++){
        int rowAnsTmp[maxn]={0};
        for(int i=M.rpos[m_row];M.data[i].x==m_row;i++){//在M中遍历M.mu行所有非零元素(m_row,b)
            int b=M.data[i].y;
            for(int j=N.rpos[b];N.data[j].x==b;j++){//在N中遍历b行的所有非零元素
                int ansCol=N.data[j].y;
                rowAnsTmp[ansCol] += M.data[i].e * N.data[j].e;
            }
        }
        for(int i=1;i<=Q.nu;i++){
            if(rowAnsTmp[i]!=0){
                Q.tu++;
                Q.data[Q.tu].e=rowAnsTmp[i];
                Q.data[Q.tu].x=m_row;
                Q.data[Q.tu].y=i;
                //printf("**%d %d %d\n",m_row,i,rowAnsTmp[i]);
            }
        }
    }
}
int main(){
    input();
    initRPOS(&M);initRPOS(&N);
    multiply();
    initRPOS(&Q);
    output(Q);
    return 0;
}