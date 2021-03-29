#include "iostream"
using namespace std;

void swap(int &a,int &b){int tmp=a;a=b;b=tmp;}

void simple_sort(int a[],int begin,int end){
    
    for(int i=begin;i<=end;i++){//i-1有序，i开始无序
        int min_index=i;
        for(int j=i+1;j<=end;j++){
            if(a[j]<a[min_index])min_index=j;
        }swap(a[i],a[min_index]);
    }
}

int main(){
    int n=5;
    int a[]={5,4,3,2,1};
    simple_sort(a,0,n-1);
    for(int i=0;i<n;i++)cout<<" "<<a[i];
}