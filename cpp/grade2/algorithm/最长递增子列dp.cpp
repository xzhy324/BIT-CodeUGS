#include <iostream>
using namespace std;
int a[10005];
int MTIS_last[10005];//【i】表示长度为i的末尾最小的序列的最后一个元素的值
int MTIS_max_length;//指示当前MTIS的最大长度,MLast数组【1：max_len】有值
int BiSearch(const int x,const int* arr,const int start,const int end){//返回x在arr【start：end】中的下标
    int p=start,r=end;
    while(p<=r){
        int mid=(p+r)/2;
        if(arr[mid]<=x)p=mid+1;
        else if(arr[mid]>x)r=mid-1;
    }
    return p;
}
int main(){
    int n;
    scanf("%d",&n);
    scanf("%d",&a[1]);
    for(int i=2;i<=n;i++)
        scanf(",%d",&a[i]);

    MTIS_last[1]=a[1];
    MTIS_max_length=1;
    for(int k=2;k<=n;k++){//已经有a[1:k-1]的mtis数组，求a[1:k]的mtis数组
        if(a[k]>=MTIS_last[MTIS_max_length]){
            MTIS_last[++MTIS_max_length]=a[k];
        }else{//能在中间找到插入位置
            int position=BiSearch(a[k],MTIS_last,1,MTIS_max_length);
            MTIS_last[position]=a[k];
        }
    }
    cout<<MTIS_max_length<<endl;
    return 0;
}