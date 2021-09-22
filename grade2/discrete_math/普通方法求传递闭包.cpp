#include "iostream"
#include "cmath"
#define N 20
int a[N*N],r[N][N][N],ns,tr[N][N]={0};
void multiply(int x,int y){//计算r【x+y】=r[x]*r[y]
    for(int i=0;i<ns;i++){
        for(int j=0;j<ns;j++){
            int sum=0;
            for(int m=0;m<ns;m++)sum+=r[i][m][x]*r[m][j][y];
            r[i][j][x+y]=sum>0?1:0;
        }
    }
}
int addtr(int x){
    int output=0;
    for(int i=0;i<ns;i++){
        for(int j=0;j<ns;j++){
            int result=tr[i][j]+r[i][j][x];
            result=result>0?1:0;
            if(result!=tr[i][j])output++;
            tr[i][j]=result;
        }
    }
    return output;
}
void PrintTR(){
    for(int i=0;i<ns;i++){
        for(int j=0;j<ns-1;j++)printf("%d ",tr[i][j]);
        printf("%d\n",tr[i][ns-1]);
    }
}
int main(){
    int input,n=0;
    while (scanf("%d",&input)!=EOF)a[n++]=input;
    ns=sqrt(n);
    addtr(1);
    for(int i=0;i<ns;i++)for(int j=0;j<ns;j++)r[i][j][1]=a[i*ns+j];
    for(int i=1;i<N;i++){
        multiply(i,1);
        if(addtr(i+1)==0)break;
    }
    PrintTR();
    return 0;
}