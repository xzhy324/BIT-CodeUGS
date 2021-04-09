#include<stdio.h>
#include<string.h> 
 int n=0,i=0,j=0,k=0,dp[3000][3000],a[3000],a1=0,a2=0,a3=0,count=0;
 
 int main()
 {
  while (scanf("%d",&n)!=EOF)
  {
   count=0;
   memset(a,0,sizeof(a));
   memset(dp,0,sizeof(dp));
   
   for (i=0;i<n;i++)
   {
   	scanf("%d:(%d)",&a1,&a2);
   	a[a1]=a[a1]+a2;
   	for (j=0;j<a2;j++)
   	{
   	 scanf("%d",&a3);
	 dp[a1][a3]=1;
	 dp[a3][a1]=1;
	 a[a3]++;	
	}
   }
   
   int num=n;
   while (num>0)
   {
   	
   	for (i=0;i<n;i++)
   	if (a[i]==1&&a[i]==0)//度为1的点和孤立的点删除
   	{
   	 num--;
	 a[i]=0;
	 break;
	} 
	
	 for(j=0;j<n;j++)
	 if (dp[i][j]==1)
	 {
	  dp[i][j]=0;
	  dp[j][i]=0;
	  num--;
	  count++; //度为1的点的父亲结点放置士兵
	  a[j]=0;
	  for (k=0;k<n;k++)
	  if (dp[j][k]==1) //删除该点及叶子结点
	  {
	   	if (a[k]==1)
	   	{
	   	 num--;
		 a[k]=0;
		 dp[j][k]=0;
		 dp[k][j]=0;	
		}
		else 
		{
		 a[k]--;
		 dp[j][k]=0;
		 dp[k][j]=0;	
		}
	  }	
	 }	
	
   }
   printf("%d\n",count);
  }
  return 0;
 }