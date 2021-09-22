#include "iostream"
#include "cstdlib"
#define N 2000
int max(int a,int b){
    return a>b?a:b;
}
int min(int a,int b){
    return a<b?a:b;
}
void swap(int *m,int *n){
    int tmp=*m;
    *m=*n;
    *n=tmp;
    return;
}
int main(){
    int t[N],nn,a,b,m,n;
    scanf("%d",&nn);
    for(int i=1;i<=nn;i++)scanf("%d",&t[i]);
    scanf("%d%d",&a,&b);
    if(t[a]==0)printf("ERROR: T[%d] is NULL\n",a);
    else if(t[b]==0)printf("ERROR: T[%d] is NULL\n",b);
    else{
        m=max(a,b);
        n=min(a,b);
        while(m!=n){
            m/=2;
            if(m<n) swap(&m,&n);
        }
        printf("%d %d\n",m,t[m]);
    }
    return 0;
}