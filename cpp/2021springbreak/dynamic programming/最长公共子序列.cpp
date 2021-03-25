//https://www.acwing.com/problem/content/solution/899/1/
//dp[i][j]表示arr1前i个，arr2前j个中的最大公共子列长度
#include "iostream"
#include "cstring"
using namespace std;
#define N 1010
int dp[N][N];
int max(int a,int b){
    return a>b?a:b;
}
int main(){
    int alen,blen;
    cin>>alen>>blen;
    char a[N],b[N];
    cin>>a>>b;
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=alen;i++){
        for(int j=1;j<=blen;j++){
            if(a[i-1]==b[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    cout<<dp[alen][blen];
    return 0;
}