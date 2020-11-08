#include "cstdio"  
#include "queue"  
#include "vector"  
#include "cstring"  
using namespace std;  
char grid[110][110][55];  
int vis[110][110][55];  
int n,m,k,sx,sy,ex,ey;  
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};  
  
struct node  
{  
    int x,y;  
    int step;  
};  
  
queue<node>q;  
  
void init()  
{  
    while(!q.empty())q.pop();  
    memset(vis,0,sizeof(vis));  
    return;  
}  
  
bool inGrid(node &a)  
{return a.x>=1&&a.y>=1&&a.x<=n&&a.y<=m;}  
bool pass(node &a)  
{  
    if(grid[a.x][a.y][a.step%k]=='.')return true;//这步的状态可走  
    else return false;  
    return true;  
}  
  
int bfs()  
{  
    init();  
    node start;  
    start.x=sx;start.y=sy;start.step=0;//从第0秒开始  
    vis[sx][sy][0]=1;  
    q.push(start);  
    while(!q.empty())  
    {  
        node now=q.front();  
        q.pop();  
        for(int i=0;i<=3;i++)  
        {  
            int x_next=now.x+dir[i][0];  
            int y_next=now.y+dir[i][1];  
            node _new;  
            _new.x=x_next;  
            _new.y=y_next;  
            _new.step=now.step+1;  
            if(inGrid(_new)&&pass(_new)&&!vis[x_next][y_next][_new.step%k])  
            {  
                if(_new.x==ex&&_new.y==ey)return _new.step;  
                vis[x_next][y_next][_new.step%k]=1;  
                q.push(_new);  
            }  
        }  
    }  
  
    return -1;  
}  
int main()  
{  
    int T;scanf("%d",&T);  
    while(T--)  
    {  
        scanf("%d %d %d",&n,&m,&k);  
        for(int i=1;i<=n;i++)  
        {  
            getchar();  
            for(int j=1;j<=m;j++)  
            {  
                char tmp;scanf("%c",&tmp);  
                if(tmp=='S')  
                {  
                    sx=i,sy=j;  
                    for(int t=0;t<=k-1;t++)grid[i][j][t]='.';  
                }  
                else if(tmp=='E')  
                {  
                    ex=i,ey=j;  
                    for(int t=0;t<=k-1;t++)grid[i][j][t]='.';  
                }  
                else if(tmp=='*')//第0秒放置路，其他时刻用#代替怪物  
                {  
                    grid[i][j][0]='.';  
                    for(int t=1;t<=k-1;t++)grid[i][j][t]='#';  
                }  
                else for(int t=0;t<=k-1;t++)grid[i][j][t]=tmp;  
            }  
        }  
          
  
        /*for(int i=1;i<=n;i++) 
        { 
            for(int j=1;j<=m;j++) 
            { 
                printf("%c",grid[i][j][0]); 
            } 
            printf("\n"); 
        }*/  
          
  
        printf("%d\n",bfs());  
  
    }  
    return 0;  
}  