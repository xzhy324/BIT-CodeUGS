#include "iostream"
typedef long long ll;
const int di = 16777216;
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int p,mi=2730;
        scanf("%d",&p);
        ll mod_di = di % p;
        if(mod_di<0)mod_di += p;
        ll result = 65536 % p;
        while(mi){
            if(mi&1){
                result = (result * mod_di) % p;
                if(result<0)result+=p;
            }
            mod_di = (mod_di * mod_di)%p;
            if(mod_di<0)mod_di+=p;
            mi>>=1;
        }
        printf("%lld\n",result);
    }
}