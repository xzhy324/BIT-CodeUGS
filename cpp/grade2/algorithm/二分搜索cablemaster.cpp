#include "iostream"  
#include "cmath"  
double length[10020];  
int main()  
{  
    int n,k;  
    scanf("%d %d",&n,&k);  
    for(int i=0;i<n;i++)scanf("%lf",&length[i]);  
    double left=0,right=0x3f3f3f3f;  
    int counter=100;  
    while(counter--)  
    {  
        double mid=(left+right)/2;  
        mid=floor(mid*100)/100;  
        int k_now=0;  
        for(int i=0;i<n;i++)k_now+=(int)(length[i]/mid);  
        if(k_now>=k)left=mid;//too short  
        else right=mid;//too long  
    }  
    printf("%.2lf\n",left);  
    return 0;  
}  