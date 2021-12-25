#include "stdio.h"
#include "math.h"

int main(){
    int m;
    scanf("%d",&m);
    int first,second,third;
//    first = lround(m*0.5);
//    second = lround(m*0.3);
    first = m*0.5 + 0.5 ;
    second = (m-first)*0.6 + 0.5;
    third = m-first-second;

    char s[3][32];
    double rate[3][3];//第i部第j天上映率
    double sum[3];
    for(int i=0;i<3;i++){
        //getchar();
        scanf("%s",s[i]);
        for(int j=0;j<3;j++){
            scanf("%lf",&rate[i][j]);
        }
        sum[i]=0;
        for(int j=0;j<3;j++){
            sum[i] += rate[i][j];
        }
    }

//    for(int i=0;i<3;i++){
//        printf("%s\n%lf\n",s[i],sum[i]);
//    }

    if(sum[0]>sum[1]){
        if(sum[2]>sum[0]){//201
            printf("%s %d\n",s[0],second);
            printf("%s %d\n",s[1],third);
            printf("%s %d\n",s[2],first);
        }else if(sum[2]<sum[1]){//012
            printf("%s %d\n",s[0],first);
            printf("%s %d\n",s[1],second);
            printf("%s %d\n",s[2],third);
        }else{//021
            printf("%s %d\n",s[0],first);
            printf("%s %d\n",s[1],third);
            printf("%s %d\n",s[2],second);
        }
    }else if(sum[0]<=sum[1]){
        if(sum[2]>sum[1]){//210
            printf("%s %d\n",s[0],third);
            printf("%s %d\n",s[1],second);
            printf("%s %d\n",s[2],first);
        }else if(sum[2]<sum[0]){//102
            printf("%s %d\n",s[0],second);
            printf("%s %d\n",s[1],first);
            printf("%s %d\n",s[2],third);
        }else{//120
            printf("%s %d\n",s[0],third);
            printf("%s %d\n",s[1],first);
            printf("%s %d\n",s[2],second);
        }
    }
    return 0;
}