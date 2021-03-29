#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int INF= static_cast<const int>(1e20);
const int N= static_cast<const int>(1.1e5);
struct node{
    double x,y;
};
node input[N],m[N];

double dist(const node &a,const node &b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

bool cmpxy(node a,node b){if(a.x==b.x)return a.y<b.y;return a.x<b.x;}

bool cmpy(node a,node b){return a.y<b.y;}

double min(double x,double y){
    return x<y?x:y;
}

double closest(node a[],int p,int r){//输入为node[p:r],返回为其中的最近点对
    //两种情况要提前考虑
    if(p==r)return INF;
    if(r==p+1)return dist(a[p],a[r]);
    //此时至少有三个元素
    sort(a+p,a+r+1,cmpxy);//按照x坐标排序
    int mid=(p+r)/2;
    double d=min(closest(a,p,mid),closest(a,mid+1,r));//求出左右两半的最小值
    //取中间一条
    int m_cnt=0;
    for(int i=p;i<=r;i++){
        if(fabs(a[i].x-a[mid].x)<=d)
            m[m_cnt++]=a[i];
    }
    //按纵坐标排序之后枚举距离
    sort(m,m+m_cnt,cmpy);
    for(int i=0;i<=m_cnt-2;i++){
        for(int j=i+1;j<m_cnt;j++){
            if(fabs(m[j].y-m[i].y)>=d)break;
            d=min(d,dist(m[i],m[j]));
        }
    }
    return d;
}

int main(){
    int n;
    while(~scanf("%d",&n) && n){
        for(int i=0;i<n;i++){
            scanf("%lf %lf",&input[i].x,&input[i].y);
        }
        printf("%.2lf\n",closest(input,0,n-1)/2.0);
    }
    return 0;
}