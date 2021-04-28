#include "iostream"
#include "cmath"
using namespace std;
double num[5];
bool backTrace(int n){//每次选两个数枚举所有可能运算结果
    if(n==1){
        if(fabs(num[1] - 24)<=1e-2)return true;
        else return false;
    }
    for(int i=1;i<=n-1;i++){
        for(int j=i+1;j<=n;j++){
            double num_i=num[i],num_j=num[j];//保存以便于还原
            num[j]=num[n];//将数列最后一个数放到 ij 其中一个的空位中，  另一个用来保存结果，这样每次长度减1且只有 ij 这两个位置有改变

            num[i]=num_i+num_j;
            if(backTrace(n-1))return true;

            num[i]=num_i*num_j;
            if(backTrace(n-1))return true;

            num[i]=num_j-num_i;
            if(backTrace(n-1))return true;

            num[i]=num_i-num_j;
            if(backTrace(n-1))return true;

            if(num_i>0){
                num[i]=num_j/num_i;
                if(backTrace(n-1))return true;
            }
            
            if(num_j>0){
                num[i]=num_i/num_j;
                if(backTrace(n-1))return true;
            }
            //枚举完这两个的所有运算，还原
            num[i]=num_i;num[j]=num_j;
        }
    }
    return false;
}
int main(){
    while(~scanf("%lf%lf%lf%lf",&num[1],&num[2],&num[3],&num[4])){
        if(backTrace(4))printf("yes\n");
        else printf("no\n");
    }
}