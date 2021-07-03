#include "iostream"
#include "cstring"
#include "queue"
//color = 0 ,未染色
//color = 1，2，染1，2
using namespace std;
const int N = 200;
int color[N],g[N][N],n;
int main(){
    memset(color,0,sizeof(color));
    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>g[i][j];
    queue<int> q;
    q.push(0);
    color[0]=1;
    bool err=false;
    while(!err&&!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i=0;i<n;i++){
            if(g[cur][i]){
                if(color[i]==0){
                    if(color[cur]==1)color[i]=2;
                    else color[i]=1;
                    q.push(i);
                }else if(color[i]==color[cur]){
                    err= true;
                }
            }
        }
    }
    if(!err)cout<<"yes\n";
    else cout<<"no\n";
}