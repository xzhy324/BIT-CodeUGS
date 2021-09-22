#include "iostream"
using namespace std;
const int N = 105;
int g[N][N],n,AS[N][N][N];//AS是可达矩阵

/*
 * 判断强连通图/单向连通图/弱连通图的方法
 * 先求出邻接矩阵的可达矩阵
 * 若可达矩阵元素全为1，则是强连通图
 * 若可达矩阵对任意ij满足a[i][j]+a[j][i]>0，则是单向连通图
 * 弱连通图使用另外的判断方式：先无向图化，再做DFS，若能搜索到所有节点，则是弱连通图
 * 弱连通图还可以这样判断：先无向图化，再求可达矩阵，若无向图化的可达矩阵元素全为1，则是弱连通图
 *
 */

void AS_times_G_Eye(int m){
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        AS[i][j][m]=0;
        for(int x=0;x<n;x++){
            if(AS[i][x][m-1]&&g[x][j]){
                AS[i][j][m]=1;
                break;
            }
        }
    }
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>g[i][j];
    for(int i=0;i<n;i++){
        AS[i][i][0]=1;
        g[i][i]=1;
    }
    for(int m=1;m<=n;m++)AS_times_G_Eye(m);//AS[][][n]是可达矩阵，懒得算最小终止乘幂，n次肯定能保证正确就是了
    
    //写的很烂的代码，判断是建立在给定图至少是弱连通图的基础上，真正的判断标准见最开始的注释
    char res = 'A';
    for(int i=0;i<n&&res=='A';i++)for(int j=0;j<n;j++){
        if(AS[i][j][n]+AS[j][i][n]==1){
            res = 'B';
            break;
        }
    }
    for(int i=0;i<n&&res =='B';i++)for(int j=0;j<n;j++){
        if(AS[i][j][n]+AS[j][i][n]==0){
            res = 'C';
            break;
        }
    }
    cout<<res<<endl;
    return 0;
}