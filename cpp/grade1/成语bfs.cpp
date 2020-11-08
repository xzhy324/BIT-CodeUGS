#include "cstdio"  
#include "queue"  
#include "vector"  
#define N 1001000  
using namespace std;  
vector <long> G[N];//用邻接表来存储  
long vis[N]={0};  
struct queElem  
{  
    long word;  
    long step;  
};  
  
queue <queElem> q;  
  
long BFS(long start_word,long end_word)  
{  
    queElem start;  
    start.step=1;  
    start.word=start_word;  
   // printf("*%ld\n",start_word);  
    vis[start_word]=1;  
    q.push(start);  
    while(!q.empty())  
    {  
        queElem now=q.front();  
        q.pop();  
        for(auto &g:G[now.word])  
        {  
           // printf("**%ld\n",g);  
            if(!vis[g])  
            {  
                //printf("*%ld\n",g);  
                if(g==end_word)return now.step+2;  
                vis[g]=1;  
                queElem _new;//new is a key word in CPP STL  
                _new.word=g;  
                _new.step=now.step+1;  
                q.push(_new);  
            }  
        }  
    }  
    return -1;  
}  
int main()  
{  
    long m;scanf("%ld",&m);  
    for(long i=1;i<=m;i++)  
    {  
        long a,b,c,d;  
        scanf("%ld %ld %ld %ld",&a,&b,&c,&d);  
        G[a].push_back(d);  
    }  
    long start,end,t1,t2,t3,t4,t5,t6;  
    scanf("%ld %ld %ld %ld",&t1,&t2,&t3,&start);  
    scanf("%ld %ld %ld %ld",&end,&t4,&t5,&t6);  
    if(t1==end&&t2==t4&&t3==t5&&t6==start)printf("1\n");  
    else printf("%ld\n",BFS(start,end));  
      
    return 0;  
} 