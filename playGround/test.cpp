#include "iostream"
#include "math.h"
typedef long long ll;
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ll p;
        scanf("%lld",&p);
        for(int i=0;i<=p-1;i++){
            ll ans = ll(pow(2,i))%p;
            if(ans<0)ans+=p;
            if(ans==i)printf("%lld\n",i);
        }
    }
}