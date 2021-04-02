#include "iostream"
using namespace std;
const int N=20000;
typedef long long ll;
ll produce_fee[N],requireAmount[N];
int main(){
    ll n,storage_fee;
    cin>>n>>storage_fee;
    for(int i=1;i<=n;i++){
        cin>>produce_fee[i]>>requireAmount[i];
    }
    ll ans=0;
    for(int n0=n;n0>=1;n0--){
        ll cost_min=produce_fee[n0];
        //int week_produce=n0;
        for(ll j=1;j<=n0-1;j++){
            int fee=produce_fee[n0-j]+storage_fee*j;
            if(fee<cost_min){
                cost_min=fee;
                //week_produce=n0-j;
            }
        }
        //cout<<"week produce:"<<week_produce<<" week sell:"<<n0<<endl;
        //cout<<"cost: "<<cost_min<<endl;
        ans+=cost_min*requireAmount[n0];
    }
    cout<<ans<<endl;
    return 0;
}