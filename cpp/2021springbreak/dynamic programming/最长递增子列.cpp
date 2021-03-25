//https://www.acwing.com/problem/content/897/
//dp[n]表示结尾下标为n的最长子列长度
#include "iostream"
using namespace std;
#define N 1010
int dp[N];
int max(int a,int b){
    return a>b?a:b;
}
int main(){
    int length;cin>>length;
    int a[N];
    for(int i=0;i<length;i++){
        cin>>a[i];
        dp[i]=1;
    }
    for(int n=1;n<length;n++){
        for(int i=0;i<n;i++){
            if(a[i]<a[n])
                dp[n] = max(dp[n], dp[i] + 1);
        }
    }
    int ans=-0x3f3f3f3f;
    for(int i=0;i<length;i++)ans=max(ans,dp[i]);//注意dp的含义
    cout<<ans;
    return 0;
}