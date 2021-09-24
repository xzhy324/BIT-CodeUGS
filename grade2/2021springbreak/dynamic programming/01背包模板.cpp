//https://www.acwing.com/problem/content/2/
//dp[i][j]表示前i件物品中，总重量恰为j时的所有方案中的最大价值
//采用滚动数组的方法
#include "iostream"
#include "cstring"
using namespace std;
#define N 1010
#define INF 0x3f3f3f3f
int dp[N];
int w[N],v[N];
int max(int a,int b){
    return a>b?a:b;
}
int main(){
    int n,volume;cin>>n>>volume;
    for(int i=1;i<=n;i++)cin>>w[i]>>v[i];
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        for(int j=volume;j>=w[i];j--){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    int ans=-INF;
    for(int j=0;j<=volume;j++){
        ans=max(ans,dp[j]);
    }
    cout<<ans;
    return 0;
}