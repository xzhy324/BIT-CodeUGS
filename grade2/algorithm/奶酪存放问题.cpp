#include<iostream>
#include<string.h>
using namespace std;
struct node {
	long long p,num,id;//价格，数量，编号
}x[10005];
long long slove(long long n,long long s)
{
	long long ans=x[0].p*x[0].num,kase=0;	
	for(long long i=1;i<n;++i)
	{
		long long tp=x[kase].p+s*(i-x[kase].id),cur=x[i].p;//一个是之前生产的实际价格，一个是当天生产的价格
		if(tp<cur)//如果之前生产划算 
		{
			ans+=tp*x[i].num; 
		}
		else
		{
			ans+=cur*x[i].num;
			kase=i;
		}
	}
	return ans;
}
int main()
{
	long long n,s;
	while(~scanf("%lld%lld",&n,&s))
	{
		for(long long i=0;i<n;++i)
		{
			scanf("%lld%lld",&x[i].p,&x[i].num);
			x[i].id=i;
		}
		printf("%lld\n",slove(n,s));
	}
	return 0;
} 