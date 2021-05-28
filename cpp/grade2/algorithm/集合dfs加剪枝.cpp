#include "iostream"
#include "algorithm"
using namespace std;
const int N =15;
int n,p[N],best=0x3f3f3f3f,cur=0;
bool chosen[N];//chosen数组表示当前已经选择的点
int minj[N];
int c[N][N];
void dfs(int t){
    if(t>n){
        best = best<cur?best:cur;
        return;
    }
    for(int i=1;i<=n;i++){//n^2搜索解空间，效率较为低下
        if(!chosen[i]&& c[t][i]+cur < best){
            int possible_min= c[t][i] + cur;
            for(int k=1;k<=n;k++){
                if(k==i||chosen[k])continue;//计算剩下未选的最小可能值作为剪枝的依据
                possible_min += minj[k];
            }
            if(possible_min<best){
                chosen[i]= true;
                cur += c[t][i];
                dfs(t+1);
                cur -= c[t][i];
                chosen[i]= false;
            }
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>c[i][j];
    for(int i=1;i<=n;i++){
        p[i]=i;
        chosen[i]=false;
        minj[i]=c[i][1];
        for(int j=2;j<=n;j++)
            minj[j]= minj[j]<c[i][j]?minj[j]:c[i][j];
    }
    cur = 0;
    dfs(1);
    cout << best << endl;
    return 0;
}