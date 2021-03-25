//https://www.acwing.com/problem/content/900/
//dp[i][j]表示下标为ij的顶点的答案,从最下层开始推
#include "iostream"
using namespace std;
#define N 510
int dp[N][N];
int a[N][N];
int max(int a,int b){
    return a>b?a:b;
}
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)
        cin>>a[i][j];
    }
    for(int i=1;i<=n;i++){
        dp[n][i]=a[n][i];
    }
    for(int i=n-1;i>=1;i--){
        for(int j=1;j<=i;j++){
            dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+a[i][j];
        }
    }
    cout<<dp[1][1];
    return 0;
}