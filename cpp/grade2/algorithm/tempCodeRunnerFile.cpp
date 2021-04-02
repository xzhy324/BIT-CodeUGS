#include "iostream"
#include "queue"
#include "vector"
const int N=30;
using namespace std;
struct Pool{
    int fi,di;
    int id;
}pool[N];
struct cmp{//对结构体定义大根堆的比较规则
    bool operator() (Pool &a,Pool &b){
        return a.fi<=b.fi;
    }
};
int main(){
    int n,total_time;
    bool format_flag=false;
    for(int i=1;i<N;i++)pool[i].id=i;
    while(~scanf("%d",&n)&&n){
        int ti[N];
        scanf("%d",&total_time);
        total_time*=12;//转换成interval,此后不应变动
        for(int i=1;i<=n;i++)scanf("%d",&pool[i].fi);
        for(int i=1;i<=n;i++)scanf("%d",&pool[i].di);
        for(int i=1;i<=n-1;i++)scanf("%d",&ti[i]);//ti[x] := time needed from x to x+1  
        
        int max_caught=0;
        int max_plan[N];
        //枚举终点为n个pool，这样路上的时间是完全确定的
        for(int end=1;end<=n;end++){
            int road_time=0;
            for(int i=1;i<=end-1;i++)road_time+=ti[i];
            int fish_time=total_time-road_time;
            int time_spent[N];
            for(int i=0;i<N;i++)time_spent[i]=0;
            int fish_caught=0;

            priority_queue <Pool,vector<Pool>,cmp> heap_max;
            for(int i=1;i<=end;i++){
                if(pool[i].fi>=0)heap_max.push(pool[i]);
            }
            while(heap_max.size()>0&&fish_time>0){//不断取出当前最优解
                Pool tmp=heap_max.top();
                heap_max.pop();
                time_spent[tmp.id]++;
                fish_time--;
                fish_caught+=tmp.fi;

                tmp.fi-=tmp.di;
                if(tmp.fi>0)heap_max.push(tmp);
            }
            printf("end:%d fish_time:%d\n",end,fish_time);
            if(fish_time>0)time_spent[1]+=fish_time;//多余的时间全部要给pool1

            if(fish_caught>max_caught){//不太优美
                max_caught=fish_caught;
                for(int i=1;i<=end;i++)max_plan[i]=time_spent[i]*5;//注意还原成分钟
                for(int i=end+1;i<=n;i++)max_plan[i]=0;
            }
        }
        if(format_flag)printf("\n");
        format_flag=true;
        for(int i=1;i<n;i++)printf("%d, ",max_plan[i]);
        printf("%d\n",max_plan[n]);
        printf("Number of fish expected: %d\n",max_caught);
    }
    return 0;
}