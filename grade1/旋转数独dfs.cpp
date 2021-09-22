#include "cstdio"
using namespace std;
int a[17][17];
int rot[4][4]={0},ans[4][4];
void printGrid(){
    for(int i=1;i<=16;i++){
            for(int j=1;j<=16;j++)printf("%2d ",a[i][j]);
            printf("\n");
        }
    for(int j=1;j<=16;j++)printf("---");printf("\n");
    return;
}
void init(){
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            rot[i][j]=0;
            ans[i][j]=3;
        }
    }
    return;
}
void getAns(){
    //printf("solution founded!\n");
    //printGrid();
    
    int rot_tmp[4][4],sum1=0,sum2=0,sumANS=0;
    for(int i=0;i<=3;i++)for(int j=0;j<=3;j++){
        rot_tmp[i][j]=(rot[i][j]+2)%4;
        sum1+=rot[i][j];
        sum2+=rot_tmp[i][j];
        sumANS+=ans[i][j];
    }
    //printf("%d %d %d\n",sum1,sum2,sumANS);
    if(sum1<sum2){
        if(sumANS>sum1)for(int i=0;i<=3;i++)for(int j=0;j<=3;j++)ans[i][j]=rot[i][j];
    }
    else{
        if(sumANS>sum2)for(int i=0;i<=3;i++)for(int j=0;j<=3;j++)ans[i][j]=rot_tmp[i][j];
    }
    return;
}

void rotate(int m[17][17],int x,int y){
        int tmp[5][5];
        for(int i=1;i<=4;i++)for(int j=1;j<=4;j++)tmp[i][j]=m[x+i-1][y+j-1];
        for(int i=x+3;i>=x;i--)for(int j=0;j<=3;j++)m[i][y+j]=tmp[j+1][4-i+x];
    return;
}
bool checkx(int x,int y){
    for(int i=1;i<=x-1;i++)if(a[i][y]==a[x][y])return false;
    return true;
}
bool checky(int x,int y){
    for(int i=1;i<=y-1;i++)if(a[x][i]==a[x][y])return false;
    return true;
}
bool check(int x,int y){
    bool flag=true;
    for(int i=0;i<=3&&flag;i++){
        for(int j=0;j<=3&&flag;j++){
            flag=checkx(x+i,y+j)&&checky(x+i,y+j);
        }
    }
    //printf("checking %d %d\n",x/4+1,y/4+1);
    return flag;
}

void dfs(int m,int n){
    if(m==13&&n==13){
        for(int i=1;i<=4;i++){
            if(i==1){
                if(check(m,n)){
                    getAns();//copy rot to rot_tmp,compare min(rot,rot_tmp) and ans, update ans    
                }
            }
            else{
                rotate(a,m,n);rot[m/4][n/4]++;
                if(check(m,n)){
                    getAns();//copy rot to rot_tmp,compare min(rot,rot_tmp) and ans, update ans    
                }
            }
        }
        rotate(a,m,n);rot[m/4][n/4]=0;//restore
        return;
    }
    else{
        if(n<13){
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(check(m,n))dfs(m,n+4);
                }
                else{
                    rotate(a,m,n);rot[m/4][n/4]++;
                    if(check(m,n))dfs(m,n+4);
                }
            }
            rotate(a,m,n);rot[m/4][n/4]=0;//restore
            return;
        }
        else if(n==13&&m<13){
            for(int i=1;i<=4;i++){
                if(i==1){
                    if(check(m,n))dfs(m+4,1);
                }
                else{
                    rotate(a,m,n);rot[m/4][n/4]++;
                    if(check(m,n))dfs(m+4,1);
                }
            }
            rotate(a,m,n);rot[m/4][n/4]=0;//restore
            return;
        }
    }
    return;
}
int main(){
    int T;scanf("%d",&T);
    while(T--)
    {
        init();
        for(int i=1;i<=16;i++)
        {
            char s[17];scanf("%s",s);
            for(int j=1;j<=16;j++)
            {
                if(s[j-1]>='0'&&s[j-1]<='9')a[i][j]=s[j-1]-'0';
                else a[i][j]=s[j-1]-'A'+10;
            }
        }
       // printGrid();
        dfs(1,1);
        //printGrid();
        int sumANS=0;
        for(int i=0;i<=3;i++)for(int j=0;j<=3;j++)sumANS+=ans[i][j];
        printf("%d\n",sumANS);
        for(int i=0;i<=3;i++)for(int j=0;j<=3;j++){
            for(int k=1;k<=ans[i][j];k++){
                printf("%d %d\n",i+1,j+1);
            }
        }
    }
    return 0;
}