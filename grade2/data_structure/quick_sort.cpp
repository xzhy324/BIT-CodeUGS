#include "iostream"
#include "cstdlib"
#include "cstring"
#define N 1000
#define cutoff 5
int mid_count=0,mid_output[N];
void swap(int *a,int *b)
{int temp=*a;*a=*b;*b=temp;}
void insertion_sort(int *arr,int len)
{
    for (int i=1;i<len;i++)
    {
        int tmp=arr[i],j;
        for (j=i-1;j>=0&&arr[j]>tmp;j--)arr[j+1]=arr[j];
        arr[j+1] = tmp;
    }
}
void quick_lmh(int a[],int start,int end)//序列三个位置选中值作为基准的快排，处理正序数列较快
{
    if(end-start<cutoff){
        insertion_sort(a+start,end-start+1);
        return;
    }
    int i=start+1,j=end,mid=(start+end)/2;

    if(a[mid]>a[end])swap(a+mid,a+end);
    if(a[start]>a[end])swap(a+start,a+end);
    if(a[mid]>a[start])swap(a+mid,a+start);//此时有a[mid]<=a[start]<=a[end]，即首位是三者的中值

    mid_output[mid_count++]=a[start];

    while(i!=j)
    {
        while(i<j&&a[j]>a[start])j--;
        while(i<j&&a[i]<a[start])i++;
        if(i!=j)swap(a+i,a+j);
    }
    if(a[start]>=a[i])swap(a+start,a+i);
    quick_lmh(a,start,i-1);
    quick_lmh(a,i+1,end);
}
int main(){
    int input[N];
    int input_amount = 0;
    char x[20];
    while(1){
        scanf("%s",x);
        if(strcmp(x,"#")==0)break;
        input[input_amount++] = atoi(x);
    }
    quick_lmh(input,0,input_amount-1);
    printf("After Sorting:\n");
    for(int i=0;i<input_amount;i++){
        printf("%d ",input[i]);
    }
    printf("\nMedian3 Value:\n");
    if(mid_count){
        for(int i=0;i<mid_count;i++)printf("%d ",mid_output[i]);
        printf("\n");
    }else printf("none\n");
    return 0;
}