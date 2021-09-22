#include <iostream>
int y[2100000];

void swap(int &a,int &b){int tmp=a;a=b;b=tmp;}

void simple_sort(int a[],int begin,int end){  
    for(int i=begin;i<=end-1;i++){//i-1有序，i开始无序
        int min_index=i;
        for(int j=i+1;j<=end;j++){
            if(a[j]<a[min_index])min_index=j;
        }
        swap(a[i],a[min_index]);
    }
}

int partition(int a[],int p,int r,int pivot){//用a[pivot]作为基准对a[p:r]进行快排分割,左半部分比较小,返回最终pivot位置
    int left=p,right=r+1,temp=a[pivot];
    swap(a[pivot],a[p]);
    while(1){
        while(a[++left]<temp&&left<right);
        while(a[--right]>temp);
        if(left>=right)break;
        swap(a[left],a[right]);
    }
    //此时已被分割为a[p:q-1],a[q],a[q+1:r],其中q=left
    a[p]=a[left];
    a[left]=temp;
    return left;
}

int select(int a[],int begin,int end,int k){//从a[begin:end]中找到第k大的数的下标
    //数量较少时不进入递归调用
    if(end-begin<75){
        simple_sort(a,begin,end);
        return begin+k-1;
    }
    //分[n/5]组寻找各组中位数
    for(int i=0;i<=(end-begin-4)/5;i++){
        //找a[begin+5*i]~a[begin+5*i+4]的中位数，与a[begin+i]调换位置
        simple_sort(a,begin+5*i,begin+5*i+4);
        swap(a[begin+i],a[begin+5*i+2]);
    }
    //对a[begin+0]~a[begin+(end-begin-4)/5]这些中位数取中位数
    int mid=select(a,begin,begin+(end-begin-4)/5,((end-begin-4)/5)/2);
    //用mid作为基准对a进行快排分割,左半部分比较小
    int partPosition=partition(a,begin,end,mid);
    int leftSideQuantity=partPosition-begin+1;
    if(k<=leftSideQuantity)return select(a,begin,partPosition,k);//总体第k小的数在左半部分，是左半部分第k小的数
    else return select(a,partPosition+1,end,k-leftSideQuantity);//总体第k小的数在右半部分，是右半部分第k-leftSideQuantitiy的数
}
int main(){
    int temp,n;
    while(scanf("%d,%d",&temp,&y[n])!=EOF){n++;}
    std::cout<<y[select(y,0,n-1,(n+1)/2)]<<std::endl;
    return 0;
}  