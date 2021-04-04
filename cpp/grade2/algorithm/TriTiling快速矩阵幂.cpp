#include <iostream>
typedef long long ll;
//f(n)=4*f(n-1)-f(n-2)&&f(1)=3&&f(0)=1,使用快速矩阵幂
const int MOD=9973;
struct matrix{
    ll data[2][2];
}a,eye;
void ResetA(){
    a.data[0][0]=4;
    a.data[0][1]=-1;
    a.data[1][0]=1;
    a.data[1][1]=0;
}
matrix multiply(const matrix &x,const matrix &y){//a times b
    matrix result;
    for(int i=0;i<=1;i++){
        for(int j=0;j<=1;j++){
            result.data[i][j]=0;
            for(int k=0;k<=1;k++){
                result.data[i][j]+=x.data[i][k]*y.data[k][j];
            }
        }
    }
    for(int i=0;i<=1;i++){
        for(int j=0;j<=1;j++){
            result.data[i][j]%=MOD;
        }
    }
    return result;
}
ll solve(int n){//assume that n>=1,return a^n times f0;
    ResetA();
    matrix result=eye;
    while(n){//取出n的二进制表示
        if(n&1){//二进制末尾是1，说明需要累加
            result=multiply(result,a);
        }
        a=multiply(a,a);//提前计算下一个幂次
        n>>=1;//推进到下一个二进制位
    }
    ll ans=((result.data[0][0]*3)%MOD+result.data[0][1]%MOD)%MOD;
    return ans<0?(ans+MOD):ans;
}
int main(){
    int n;
    eye.data[0][0]=1;eye.data[0][1]=0;
    eye.data[1][0]=0;eye.data[1][1]=1;
    while(~scanf("%d",&n)&&n!=-1){
        if(n%2)printf("0\n");
        else if(n/2==0)printf("1\n");
        else if(n/2==1)printf("3\n");
        else printf("%lld\n",solve(n/2-1));
    }
    return 0;
}