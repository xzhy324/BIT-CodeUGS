#include "iostream"
#define N 1000
using namespace std;
int n,a[N];
void swap(int *x,int *y){int tmp=*x;*x=*y;*y=tmp;}
void HeapAdjust(int point,int end) {
    while(point<end){
        int lc=2*point,rc=2*point+1;
        if(rc>=end+2)break;
        else if(rc==end+1){//只有左子树
            if(a[point]<a[lc])swap(a+point,a+lc);
            break;
        }else{//左右子树都在
            int max_son=a[lc]>a[rc]?lc:rc;
            if(a[max_son]<=a[point])break;//已经完成调整
            else{
                swap(a+max_son,a+point);
                point=max_son;
            }
        }
    }
}
void PopHeap(int end) {
    swap(a+1,a+end);
    HeapAdjust(1,end-1);
}
int main(){
    cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n/2;i>=1;i--)HeapAdjust(i,n);
    for(int i=n;i>=1;i--)PopHeap(i);
    for(int i=1;i<=n;i++)cout<<a[i]<<" ";
}