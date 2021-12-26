#include "string.h"
#include "stdio.h"

char g[1002][1002];
char ans[1000005];
int n,m,k,sx,sy;

int min(int x,int y){
    return x<y?x:y;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        getchar();
        for(int j=1;j<=m;j++)
        {
            char tmp;scanf("%c",&tmp);
            if(tmp=='X'){
                sx = i;
                sy = j;
                g[i][j] = '*';
            }else {
                g[i][j] = tmp;
            }
        }
        //getchar();
    }
    for(int i = 0;i<=n+1;i++){
        g[i][0]='*';
        g[i][m+1]='*';
    }
    for(int j = 0;j<=m+1;j++){
        g[0][j]='*';
        g[n+1][j]='*';
    }

    if(k%2){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    int x = sx,y = sy;
    int prior=4;
    /*
     * 4 == 向上但没有向
     *
     */
    for(int k0=1;k0<=k/2;k0++){
        if(g[x-1][y]=='.'){
            ans[k0]='U';
            x--;
        }else if(g[x][y+1]=='.'){
            prior = min(prior,3);
            y++;
            ans[k0]='R';
        }else if(g[x][y-1]=='.'){
            prior = min(prior,2);
            y--;
            ans[k0]='L';
        }else if(g[x+1][y]=='.'){
            x++;
            prior = min(prior,1);
            ans[k0]='D';
        }
    }
    for(int k0=k/2+1;k0<=k;k0++){
        int img = k-k0;
        if(ans[img]=='R')ans[k0]='L';
        if(ans[img]=='L')ans[k0]='R';
        if(ans[img]=='D')ans[k0]='U';
        if(ans[img]=='U')ans[k0]='D';
    }

    for(int i=1;i<=k;i++){
        printf("%c",ans[i]);
    }
    printf("\n");
}