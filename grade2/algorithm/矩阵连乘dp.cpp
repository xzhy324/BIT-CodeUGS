#include <iostream>
using namespace std;
const int N=2005;
int n,q[N],m[N][N],s[N][N];//m[i][j]表示i到j合并所需的最小代价，s[i][j]表示从i到j合并的分段点
void traceback(int i, int j) {
    if(i==j)cout<<"A"<<i;
    else{
        cout<<"(";
        traceback(i,s[i][j]);
        traceback(s[i][j]+1,j);
        cout<<")";
    }
}

int main(){

    cin>>n;
    for(int i=0;i<=n;i++){cin>>q[i];}

    for(int i=1;i<=n;i++)m[i][i]=0;//初始化

    for(int r=1;r<=n-1;r++){
        for(int i=1;i<=n-r;i++){//计算m[i][j]的值
            int j=i+r;
            s[i][j]=i;//随便取一种分段方式
            m[i][j]=m[i][i]+m[i+1][j]+q[i-1]*q[i]*q[j];//将m[i][j]初始化为上述分段的代价
            for(int k=i+1;k<=j-1;k++){//更新最小代价与对应分段点
                int t=m[i][k]+m[k+1][j]+q[i-1]*q[k]*q[j];
                if(m[i][j]>t){
                    m[i][j]=t;
                    s[i][j]=k;
                }
            }
        }
    }
    cout<<m[1][n]<<endl;
    if(n==1){
        cout<<"(A1)";
    }else traceback(1,n);
    cout<<endl;
    return 0;
}