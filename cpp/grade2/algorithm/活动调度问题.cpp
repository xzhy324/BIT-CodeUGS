#include "iostream"
#include "algorithm"
using namespace std;
const int N=1000005;
struct TIMELINE{
    int stap;
    int type;//1 means start,-1 means end
}Timeline[2*N];

bool cmp(const TIMELINE &a,const TIMELINE &b){
    if(a.stap==b.stap)return a.type<b.type;
    return a.stap<b.stap;
}
int main(){
    int n,start,end;
    int stapCnt=0;
    cin>>n;
    for(int i=0;i<n;i++){
        scanf("%d%d",&start,&end);
        Timeline[stapCnt].stap=start;
        Timeline[stapCnt++].type=1;
        Timeline[stapCnt].stap=end;
        Timeline[stapCnt++].type=-1;
    }
    sort(Timeline,Timeline+stapCnt,cmp);
    int ans=0,curSpace=0;
    for(int i=0;i<stapCnt;i++){
        curSpace+=Timeline[i].type;
        if(curSpace>ans)ans=curSpace;
    }
    cout<<ans<<endl;
    return 0;
}