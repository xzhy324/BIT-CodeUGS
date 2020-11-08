/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{   int         data;
    struct node * next;
} NODE;

void output( NODE *, int );
void change( int, int, NODE * );

void output( NODE * head, int kk )
{   int k=0;

	printf("0.");
	while ( head->next != NULL && k<kk )
	{   printf("%d", head->next->data );
		head = head->next;
		k ++;
	}
	printf("\n");
}

int main()
{   int n, m,k;
	NODE * head;

	scanf("%d%d%d", &n, &m, &k);
	head = (NODE *)malloc( sizeof(NODE) );
	head->next = NULL;
	head->data = -1;
	change( n, m, head );
	output( head,k );
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
int check(int a[],int point)
{
	int ans=-1;
	for(int i=0;i<=point-1;i++)if(a[i]==a[point])ans=i;
	return ans;
}
void change(int a,int b,NODE* head)
{
	int r[1000],q[1000],point=1,flag=0;
	r[0]=a;
	for(;!flag;)
	{
		q[point]=(r[point-1]*10)/b;
		r[point]=(r[point-1]*10)%b;
		if(r[point]==0)flag=1;
		if(check(r,point)!=-1)flag=2;
		point++;
	}
	point--;
	if(flag==1)
	{
		for(int i=1;i<=point;i++)
		{
			NODE *p=(NODE*)malloc(sizeof(NODE));
			head->next=p;
			p->data=q[i];
			p->next=NULL;
			head=p;
		}
	}
	else if(flag=2)
	{
		int qstart=check(r,point)+1;
		for(int i=1;i<=qstart;i++)
		{
			NODE *p=(NODE*)malloc(sizeof(NODE));
			head->next=p;
			p->data=q[i];
			p->next=NULL;
			head=p;
		}
		head->next=head;
		for(int i=qstart+1;i<=point;i++)
		{
			NODE *p=(NODE*)malloc(sizeof(NODE));
			p->data=q[i];
			p->next=head->next;
			head->next=p;
			head=p;
		}
	}
}