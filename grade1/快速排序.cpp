#include <stdio.h>
void intswap(int *a,int *b)
{*a=*a^*b;*b=*a^*b;*a=*a^*b;return;}
void quick_sort(int a[],int start,int end)
{
	printf("start:%d end:%d\n",start,end);
	if(start>=end)return;
	int i=start+1,j=end;
	while(i!=j)
	{
		while(i<j&&a[j]>=a[start])j--;
		while(i<j&&a[i]<=a[start])i++;
		if(i<j)intswap(a+i,a+j);
	}
	if(a[start]>a[i])
	{
		intswap(a+start,a+i);	
		quick_sort(a,start,i-1);
		quick_sort(a,i+1,end);
	}
	else
	{	
		quick_sort(a,start,i-1);
		quick_sort(a,i,end);
	}
	return;
}
main()
{
	int n,a[20];
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	scanf("%d",&a[i]);
	quick_sort(a,0,n-1);
	for(int i=0;i<n;i++)
	printf("%d ",a[i]);
}
