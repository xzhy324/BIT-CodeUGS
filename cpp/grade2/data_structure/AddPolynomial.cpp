#include "cstdio"
#include "cstdlib"
using namespace std;
struct polynomial
{
	int coef; //系数
	int expn; //指数
	polynomial *next;
};
void CreatePolyn(polynomial &P, int m)
{
	polynomial *head = &P;
	
	if(m==0)
	{
		head->next=(polynomial *)malloc(sizeof(polynomial));
		head->next->coef=0;
		head->next->expn=0;
		head->next->next=NULL;
		return;
	}

	for (int i = 1; i <= m; i++)
	{
		int coef, expn;
		scanf("%d %d", &coef, &expn);
		polynomial *tmp = (polynomial *)malloc(sizeof(polynomial));
		tmp->coef = coef;
		tmp->expn = expn;
		tmp->next = NULL;
		head->next = tmp;
		head = head->next;
	}
}
void PrintPolyn(polynomial P)
{
	polynomial *head = P.next; //头指针节点不含数据
	while (head->next != NULL)
	{
		printf("<%d,%d>,", head->coef, head->expn);
		head = head->next;
	}
	printf("<%d,%d>\n", head->coef, head->expn);
}
void AddPolyn(polynomial &Pa, polynomial Pb)
{
	polynomial *head = &Pa;
	if (head->next->coef == 0) //丢掉<0,0>
	{
		free(head->next);
		head->next = NULL;
	}
	polynomial *a = &Pa, *b = &Pb;
	while (a->next && b->next)
	{
		if (a->next->expn < b->next->expn)
		{
			a = a->next;
			continue;
		}
		if (a->next->expn > b->next->expn)
		{
			polynomial *tmp = (polynomial *)malloc(sizeof(polynomial));
			tmp->coef = b->next->coef;
			tmp->expn = b->next->expn;
			tmp->next = a->next;
			a->next = tmp;
			a = a->next;
			b = b->next;
		}
		if (a->next->expn == b->next->expn)
		{
			int sum = a->next->coef + b->next->coef;
			if (sum != 0)
			{
				a->next->coef = sum;
				a = a->next;
				b = b->next;
			}
			else
			{
				polynomial *tmp = a->next;
				a->next = a->next->next;
				free(tmp);
				b = b->next;
			}
		}
	}

	while (b->next != NULL) // 把剩余的b接到a后面
	{
		a->next = (polynomial *)malloc(sizeof(polynomial));
		a = a->next;
		a->coef = b->next->coef;
		a->expn = b->next->expn;
		a->next = NULL;
		b = b->next;
	}
	if (head->next == NULL)//不剩东西的时候补一个<0,0>
	{
		head->next = (polynomial *)malloc(sizeof(polynomial));
		head = head->next;
		head->coef = 0;
		head->expn = 0;
		head->next = NULL;
	}
}
int main()
{
	char TYPE;
	TYPE = getchar();
	if (TYPE == '0')
		return 0;
	else if (TYPE == '1')
	{
		int m1, m2, m3;
		polynomial Pa, Pb, Pc;
		scanf("%d", &m1);CreatePolyn(Pa, m1);
		scanf("%d", &m2);CreatePolyn(Pb, m2);
		scanf("%d", &m3);CreatePolyn(Pc, m3);
		PrintPolyn(Pa);PrintPolyn(Pb);PrintPolyn(Pc);
		AddPolyn(Pa, Pb);
		PrintPolyn(Pa);
		AddPolyn(Pa, Pc);
		PrintPolyn(Pa);
	}
	return 0;
}