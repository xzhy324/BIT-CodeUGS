#include "cstdio"
#include "algorithm"
#include "vector"
#define N 201000
using namespace std;
vector <int> g[N];
int a[N],sortFlag[N],findRoot[N]={0},ans[N],ansNow=1;
void dfs(int present,int pflag)
{
    if(g[present].size()==0)
    {
        ans[ansNow++]=a[present];
        return;
    }
    else 
    {
        int ansNowTmp=ansNow;
        ans[ansNow++]=a[present];
        for(auto &sub_p:g[present])dfs(sub_p,  sortFlag[sub_p]&&!sortFlag[present]  );
            /*if father node flag==0then doesn't matter,, 
            if it's 1 then all his sons don't need to be sorted 
            until the father node is archieved again.*/
        if(pflag)sort(&ans[ansNowTmp],&ans[ansNow]);
        return;
    }
    return;
}
int main()
{
    int n,root;scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&sortFlag[i]);
    for(int i=1;i<=n-1;i++)
    {
        int x,y;scanf("%d %d",&x,&y);
        findRoot[y]++;
        g[x].push_back(y);
    }
    for(int i=1;i<=n;i++)if(!findRoot[i])root=i;
    for(auto &p:g)sort(p.begin(),p.end());
    dfs(root,sortFlag[root]);
    printf("[");
    for(int i=1;i<=n-1;i++)printf("%d,",ans[i]);
    printf("%d]\n",ans[n]);
    return 0;
}