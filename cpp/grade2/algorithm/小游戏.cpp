#include "iostream"
using namespace std;
const int N=1505;
int degree[N];
int graph[N][N];
void init(){
    for(int i=0;i<N;i++)degree[i]=0;
    for(int i=0;i<N;i++)for(int j=0;j<N;j++)graph[i][j]=0;
}
void input(int n){
    int id,length;
    for(int i=0;i<n;i++){
        scanf("%d:(%d)",&id,&length);
        degree[id]+=length;//出度增加
        int vtemp;
        for(int i=0;i<length;i++){
            scanf("%d",&vtemp);
            graph[vtemp][id]=1;
            graph[id][vtemp]=1;
            degree[vtemp]++;//入度增加
        }
    }
}
void tackle(int n){
    int result=0;
    int v_now=n;
    while(v_now>0){

        int d1_vertex;
        for(d1_vertex=n-1;d1_vertex>=0;d1_vertex--){
            if(degree[d1_vertex]==1){
                degree[d1_vertex]=0;
                v_now--;
                break;
            }
        }

        int d1_father;
        for(d1_father=n-1;d1_father>=0;d1_father--){
            if(graph[d1_vertex][d1_father]==1){
                break;
            }
        }

        degree[d1_father]=0;
        v_now--;
        result++;
        //graph[d1_vertex][d1_father]=0;
        //graph[d1_father][d1_vertex]=0;

        for(int adj=0;adj<n;adj++){
            if(graph[d1_father][adj]==1){
                graph[d1_father][adj]=0;
                graph[adj][d1_father]=0;
                degree[adj]--;
                if(degree[adj]==0)v_now--;
            }
        }
    }
    printf("%d\n",result);
}
int main(){
    int n;
    while(cin>>n){
        init();
        input(n);
        tackle(n);
    }
    return 0;
}
