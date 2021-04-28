//借鉴了单调栈的思路，核心点在于只有遇到下降的块的时候才更新ans，同时要求记录每块板的前置连续高板（不在栈中）
#include "iostream"
#include "stack"
using namespace std;
const int maxn=100005;
typedef long long ll;
struct wood{
    int id,h;
    int pre; //该木板之前有多少个连续的比该木板高的木板（注意这些木板均不在栈中）
}a[maxn];
stack<wood>accent;
int main()
{
    ll ans,n;
    while(!accent.empty())accent.pop();
    while(cin>>n&&n){
        ans=0;
        for(int i=0; i<n; i++){
            a[i].id=i;a[i].pre=0;
            scanf("%d",&a[i].h);
            while(!accent.empty() && a[i].h<accent.top().h){
                wood tmp=accent.top(); accent.pop();
                a[i].pre+=tmp.pre+1;//弹出的自身+前面的高板
                //对tmp板为终点更新最大值
                ans=max(ans,tmp.h*(ll)(a[i].id-tmp.id+tmp.pre));
            }
            accent.push(a[i]);
        }
        while(!accent.empty()){
            wood tmp=accent.top(); accent.pop();
            ans=max(ans,tmp.h*(ll)(n-tmp.id+tmp.pre));
        }
        printf("%lld\n",ans);
    }
    return 0;
}