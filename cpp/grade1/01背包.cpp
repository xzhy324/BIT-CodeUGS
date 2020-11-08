#include<cstdio>
int max(int a, int b)//取最大值函数
{return a > b ? a : b;}
。
struct Thing
{
    int w;
    int v;
}list[101];

int dp[101][1001];

int main()
{
    int s, n;//背包容量和物品总数
    while (scanf("%d%d", &s, &n) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &list[i].w, &list[i].v);//读入每个物品的体积和价值
        }
        for (int i = 0; i <= s; i++) dp[0][i] = 0;//初始化二维数组
        
        for (int i = 1; i <= n; i++)//循环每个物品，执行状态转移方程
        {
            for (int j = s; j >= list[i].w; j--)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - list[i].w] + list[i].v);
            }
            for (int j = list[i].w - 1; j >= 0; j --)
            {
                dp[i][j] = dp[i - 1][j];//对于装不下的情况，直接和上一个的价值函数相等
            }
         printf("%d\n", dp[n][s]);
    return 0;
}