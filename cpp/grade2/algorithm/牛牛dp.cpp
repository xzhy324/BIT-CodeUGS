#include "iostream"
#define up 0
#define down 1
using namespace std;
const int N=1000;

int dp[N][2];//dp[i][up]表示x[1:i]的最大可能距离，dp[i][down] 表示x[1:i]的最小可能距离
int n,ln,dn;
int l[N][N],d[N][N];

void init(){
    for(int i=0;i<N;i++)for(int j=0;j<N;j++)
        {l[i][j]=0;d[i][j]=0;}
    for(int i=0;i<N;i++)
        {dp[i][up]=0;dp[i][down]=0;}
}
int main(){
    init();

    return 0;
}