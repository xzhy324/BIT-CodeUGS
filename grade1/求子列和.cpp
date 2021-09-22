#include <stdio.h>
long max(long a,long b)
{return a>b?a:b;}
long baoli(int a[],int n)//�����㷨�����Ӷ�Ϊo��n^3�� 
{
	long ans=a[0];
	for(int len=1;len<=n;len++)
	{
		for(int start=0;start<=n-len;start++)
		{	
			long sum=0;
			for(int i=0;i<=len-1;i++)sum+=(long)a[start+i];
			ans=max(ans,sum);
		}	
	}
	return ans;
}
long baoli_youhua(int a[],int n)//��ǰ���ǰi���sumi�����i��j���Ϊsumj=sumi �����Ӷ�Ϊo��n^2�� 
{
	long ans=a[0],sum[200]={0};
	
	for(int i=1;i<=n;i++)
	for(int j=0;j<=i;j++)
	sum[i]+=(long)a[j];//���Ӷȿ�����o(n^2) 
	
	for(int len=1;len<=n;len++)
	for(int start=0;start<=n-len;start++)
	ans=max(ans,sum[start+len+1]-sum[start]);	
	
	return ans;
}

long divide_and_merge(int a[],int start,int end)//�鲢��˼�������кͣ����Ӷ�Ϊo(nlogn) 
{
	if(start==end)return a[start];
	
	int mid=start+(end-start)/2;
	
	long right=divide_and_merge(a,start,mid);
	long left=divide_and_merge(a,mid+1,end);
	
	long midright=a[mid],midleft=a[mid+1],sumr=0,suml=0;//���Խ���������� 
	int x=mid,y=mid+1;
	
	while(x>=start)
	{
		sumr+=(long)a[x];
		midright=max(midright,sumr);
		x--;
	}
	while(y<=end)
	{
		suml+=(long)a[y];
		midleft=max(midleft,suml);
		y++;
	}
	return max(max(right,left),midright+midleft);
} 

long prefix_sum(int a[],int n) //��ÿһ�����ܵ����ǰ׺�ͣ�ȷ�����Ӧ��ǰ�����е���Сǰ׺�� 
{
	long sum[201]={0},maxx=a[0],minx=0;
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i-1];
		if(maxx<sum[i])
		{
			maxx=sum[i];
			for(int j=0;j<=i-2;j++)	minx=minx<sum[j]?minx:sum[j];
		}
	}
	return maxx-minx;
}

long intergrate(int a[],int n)//���������  �����ۼӺͣ�һ����С���㣨���������Ϊ��ֵ�����ۼӺ��������¿�ʼ�����ۼӺ͡��ر�ע����ʼ��һ�θ�ֵ�ᱻ����
//ȡ��Щ���е����ֵ
{
	long sum=0,maxx=a[0];
	for(int i=1;i<=n;i++)
	{
		sum+=(long)a[i-1];
		if(sum<0)sum=0;
		else if(sum>maxx)maxx=sum;
	}
	return maxx;
}

long dp(int a[],int n)
{
	if(n==1&&a[n]>0)return a[n];
	if(n==1&&a[n]<=0)return 0;
	else return max(dp(a,n-1),0)+a[n];
}

main()
{
	int a[200],n;
	long ans;
	scanf("%d",&n);
	for(int i=0;i<=n-1;i++)scanf("%d",&a[i]);
	
	ans=dp(a,n);
	printf("%ld\n",ans);
	
} 
