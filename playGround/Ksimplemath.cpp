#include "iostream"
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        if(n==4)printf("1 1 2\n");
        else{
            int mod = n%3;
            if(mod==0){
                int ans = n/3;
                printf("%d %d %d\n",ans,ans,ans);
            }else{
                if((n-1)%2==0){
                    int ans = (n-1)>>1;
                    printf("1 %d %d\n",ans,ans);
                }else{
                    int ans = (n-2)>>1;
                    printf("2 %d %d\n",ans,ans);
                }
            }
        }
    }
}