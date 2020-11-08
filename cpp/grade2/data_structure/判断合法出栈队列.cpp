#include "bits/stdc++.h"
using namespace std;
#define N 10000
int main()
{
    int n,m,flag=0;
    scanf("%d%d",&n,&m);
    while(n+m)
    {
        flag++;
        if(flag!=1)printf("\n");
        int p[N];
        for(int i=1;i<=n;i++)p[i]=i;

        for(int m0=1;m0<=m;m0++)
        {
            stack<int>a;

            int q[N],qmark=1,pmark=1;
            for(int i=1;i<=n;i++)scanf("%d",&q[i]);
            
            while(qmark<=n)
            {

                if(p[pmark]==q[qmark])//1-n队列还未入栈时遇见q中一样的直接一起出栈
                {
                    pmark++;
                    qmark++;
                }
                else if(!a.empty()&&a.top()==q[qmark])//已入栈的p队列遇见和q一样的一起出栈
                {
                    qmark++;
                    a.pop();
                }
                else//1.模拟序列1-n入栈过程
                {
                    if(pmark<=n)
                    {
                        a.push(p[pmark]);
                        pmark++;
                    }
                    else if(pmark>n)break;//下标会越界
                }
            }
            if(a.empty())printf("Yes\n");
            else printf("No\n");
        }
        scanf("%d%d",&n,&m);
    }
    return 0;
}