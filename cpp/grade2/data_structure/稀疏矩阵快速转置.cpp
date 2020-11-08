#include "cstdio"
const int maxn = 20000;
struct triple ///三元组表示行标列标以及元素值
{
    int i, j;
    int elem;
};
struct SpareMatrix
{
    triple data[maxn];
    int m, n, t; //矩阵的行数，列数，非零元个数
} matrix_s,matrix_t;
int main()
{
    int num[maxn];//列非零元个数
    int cpot[maxn];//列首非零元位置
    for(int i=1;i<=maxn-1;i++)num[i]=0;

    scanf("%d %d %d", &matrix_s.m, &matrix_s.n, &matrix_s.t);
    matrix_t.m=matrix_s.n;
    matrix_t.n=matrix_s.m;
    matrix_t.t=matrix_s.t;

    for (int i = 1; i <= matrix_s.t; i++)
    {
        scanf("%d %d %d", &matrix_s.data[i].i, &matrix_s.data[i].j, &matrix_s.data[i].elem);
        ++num[matrix_s.data[i].j];//确定每列非零元个数
    }

    cpot[1]=1;
    for(int i=2;i<=matrix_s.n;i++)
        cpot[i]=cpot[i-1]+num[i-1];//列首非零元位置=上一个列首非零元位置+上一个列首非零元个数

    int copy_cpot[maxn];
    for(int i=1;i<=matrix_s.n;i++)copy_cpot[i]=cpot[i];

    for(int i=1;i<=matrix_s.t;i++)
    {
        int colomn=matrix_s.data[i].j;
        int position=cpot[colomn];//position指示s[i]在t[]中的位置为position
        matrix_t.data[position].i=matrix_s.data[i].j;
        matrix_t.data[position].j=matrix_s.data[i].i;
        matrix_t.data[position].elem=matrix_s.data[i].elem;
        cpot[colomn]++;
    }
    printf("num:");
    for(int i=1;i<=matrix_s.n;i++)printf("%d,",num[i]);
    printf("\n");
    printf("cpot:");
    for(int i=1;i<=matrix_s.n;i++)printf("%d,",copy_cpot[i]);
    printf("\n");
    for(int i=1;i<=matrix_t.t;i++)printf("%d,%d,%d\n",matrix_t.data[i].i,matrix_t.data[i].j,matrix_t.data[i].elem);
    
    return 0;
}