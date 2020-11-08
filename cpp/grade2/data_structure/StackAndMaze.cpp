#include "cstdio"
#include "stack"
using namespace std;
const int maxn=100;
struct elem{
    bool iswall;
    bool arrived;
}maze[maxn][maxn];
void initMaze(){
    for(int i=0;i<maxn;i++)
    for(int j=0;j<maxn;j++){
        maze[i][j].iswall=true;
        maze[i][j].arrived=false;
    }
}
stack<elem>list;
int main(){
    initMaze();
    int m,n;scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        scanf("%d",&maze[i][j].iswall);
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        printf("%d",maze[i][j].iswall);
    }
    list.push(maze[1][1]);
    maze[1][1].arrived=true;
    return 0;
}