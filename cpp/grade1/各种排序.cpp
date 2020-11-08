#include <stdio.h>
/*��������*/
void swap(int *a,int *b)
{int temp=*a;*a=*b;*b=temp;return;}
void bubble_sort(int a[],int n)//ð������ 
{
	for(int i=1;i<=n-1;i++)//n-1�� 
	for(int j=0;j<n-i;j++)//��i���ж�n-i-1�� 
	if(a[j]>a[j+1])swap(a+j,a+j+1);//��ͷ��ʼ�жϣ���˴�����������β 
	return;
}
void selection_sort(int a[],int n)//ѡ������ 
{	
	for(int j=1;j<=n-1;j++)//����n-1�֣���i��ȷ����i-1������ȡÿ����С�����ڶ��ף� 
	{	
		int mark=j-1;
		for(int i=j;i<=n-1;i++)if(a[i]<a[mark])mark=i;
		swap(a+j-1,a+mark);
	}
	return;
}
void insertion_sort(int a[],int n)//�������� 
{
	int b[1024]={a[0]},bcount=1;
	for(int i=1;i<=n-1;i++)//���ν�a����b 
	{
		if(a[i]<=b[0])//a��i����С 
		{
			for(int j=bcount-1;j>=0;j--)b[j+1]=b[j];
			b[0]=a[i];bcount++;
		}
		else//a��i���м� 
		{
			int j=bcount-1;
			for(j=0;j<=bcount-2;j++)
			{
				if(a[i]<=b[j+1])
				{
					for(int k=bcount-1;k>=j+1;k--)b[k+1]=b[k];
					b[j+1]=a[i];bcount++;
				}
			}
			if(j==bcount-1)//a��i��ĩβ�������ǣ���ֹԽ�磩 
			{
				b[j+1]=a[i];bcount++;
			}
		}
	}
	for(int i=0;i<n;i++)a[i]=b[i];
	return;
}
void quick_stationary(int a[],int start,int end)//�̶���λ��Ϊ��׼���п���
{
	if(start>=end)return;
	int i=start+1,j=end;
	while(i!=j)//��ͷ�ҽ��� 
	{
		while(i<j&&a[j]>=a[start])j--;
		while(i<j&&a[i]<=a[start])i++;
		if(i<j)swap(a+i,a+j);
	}
	if(a[start]>a[i])
	{
		swap(a+start,a+i);	
		quick_stationary(a,start,i-1);//�Խ�����ָ���������������� 
		quick_stationary(a,i+1,end);
	}
	else//�ر�ע�⵱��׼С��������ʱ��Ҫ�Ի�׼���������������򣬶��������������������������� 
	{	
		quick_stationary(a,start,i-1);
		quick_stationary(a,i,end);
	}
	return;
}
void quick_lmh(int a[],int start,int end)//��������λ��ѡ��ֵ��Ϊ��׼�Ŀ��ţ������������нϿ�
{
	if(start==end)return;
	int i=start+1,j=end,mid=start+(end-start)/2;
	
	if(a[mid]>a[end])swap(a+mid,a+end);
	if(a[start]>a[end])swap(a+start,a+end);
	if(a[mid]>a[start])swap(a+mid,a+start);//��ʱ��a[mid]<=a[start]<=a[end]������λ�����ߵ���ֵ 
	
	while(i!=j)
	{
		while(i<j&&a[j]>=a[start])j--;
		while(i<j&&a[i]<=a[start])i++;
		if(i!=j)swap(a+i,a+j);
	}
	if(a[start]>a[i])
	{
		swap(a+start,a+i);
		quick_lmh(a,start,i-1);
		quick_lmh(a,i+1,end);
	}
	else
	{
		quick_lmh(a,start,i-1);
		quick_lmh(a,i,end);
	}
	return;
}
void merge_sort(int a[],int start,int end)//�鲢���򣬷���˼�� 
{
	if(start>=end)return;
	else if(start==end-1)
	{
		if(a[start]>a[end])swap(a+start,a+end);
		return;
	}
	
	int mid=start+(end-start)/2;
	merge_sort(a,start,mid);
	merge_sort(a,mid+1,end);
	
	int alen=mid-start+1,blen=end-mid,len=end-start+1;//�ϲ������� 
	int temp[1024],tmark=0;
	int x=start,y=mid+1;
	while(x<=mid&&y<=end)
	{
		if(a[x]==a[y])
		{
			temp[tmark++]=a[x++];
			temp[tmark++]=a[y++];
		}
		else if(a[x]>a[y])
			temp[tmark++]=a[y++];
		else if(a[x]<a[y])
			temp[tmark++]=a[x++];		
	}
	while(x<=mid)temp[tmark++]=a[x++];
	while(y<=end)temp[tmark++]=a[y++];	
	
	for(int i=0;i<=tmark-1;i++)a[start+i]=temp[i];
	
	return;
}
void shell_sort(int a[],int n)//ϣ�����򣬱�������һ�ַ����������
{
	return;
}
void heap_sort(int a[],int n)//�����򣬱�������һ�����öѽṹ��ѡ������
{
	return;
}
int main()
{
	k:
	int n,a[1024],num;
	printf("enter n:");scanf("%d",&n);
	printf("enter array[%d]:\n",n);
	for(int i=0;i<=n-1;i++)scanf("%d",a+i);
	printf("1.bubble 2.selection 3.insertion 4.quick:stationary 5.quick:low/mid/high 6.merge\nenter your choice:");
	scanf("%d",&num);
	switch(num)
	{
		case 1:bubble_sort(a,n);break;
		case 2:selection_sort(a,n);break;
		case 3:insertion_sort(a,n);break;
		case 4:quick_stationary(a,0,n-1);break;
		case 5:quick_lmh(a,0,n-1);break;
		case 6:merge_sort(a,0,n-1);break;
	}
	printf("ANS=\n");	
	for(int i=0;i<=n-1;i++)printf("%d ",*(a+i));
	printf("\n-------------------------------\n\n");
	goto k;
	return 0;
}
