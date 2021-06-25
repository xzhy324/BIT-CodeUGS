#include "iostream"
#include "algorithm"
using namespace std;

const int N = 500;

class Set{//并查集算法
private:
    int p[N],rank[N],n;
public:
    explicit Set(int scale=0){
        n=scale;
        for(int i=0;i<=n;i++){
            p[i]=i;
            rank[i]=0;
        }
    }
    int Find(int x){
        if(x!=p[x])
            p[x]= Find(p[x]);
        return p[x];
    }
    void Link(int x,int y){
        if(rank[x]>rank[y]){
            p[y]=x;
        }else{
            p[x]=y;
            if(rank[x]==rank[y])
                rank[y]++;
        }
    }
    void Union(int x,int y){
        Link(Find(x),Find(y));
    };
};

struct LINE{
    int a,b;
    int w;
    bool chosen;
    bool friend operator<(const LINE &x,const LINE &y){return x.w<=y.w;}
}lines[N];

int main(){
    int sum=0, n=0,m=0;;
    cin>>n>>m;
    Set us(n);
    for(int m0=1;m0<=m;m0++){
        cin>>lines[m0].a>>lines[m0].b>>lines[m0].w;
        lines[m0].chosen = false;
    }
    sort(&lines[1],&lines[m+1]);
    for(int cur=1;cur<=m;cur++){
        if(us.Find(lines[cur].a) != us.Find(lines[cur].b)){
            us.Union(lines[cur].a,lines[cur].b);
            lines[cur].chosen= true;
            sum+=lines[cur].w;
        }
    }
    for(int i=1;i<=m;i++){
        if(lines[i].chosen)
            cout<<lines[i].a<<" "<<lines[i].b<<endl;
    }
    bool connected = true;//通过扫一遍染色来判断是否是连通图
    for(int i=1;i<=n;i++){
        if(us.Find(i)!=us.Find(1)){
            connected = false;
            break;
        }
    }
    if(connected){
        if(sum==0)cout<<"0 \n";
        else cout<<sum<<endl;
    }else cout<<"-1"<<endl;
    return 0;
}