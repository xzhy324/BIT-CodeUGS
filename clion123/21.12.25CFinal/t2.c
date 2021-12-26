#include <stdio.h>
#include <math.h>

float dist(float x1,float y1,float x2,float y2){
    return sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main() {
    int n;
    scanf("%d",&n);
    float cord[10005][2];
    cord[0][0]=0.0f;
    cord[0][1]=0.0f;
    for(int i=1;i<=n;i++){
        scanf("%f%f",&cord[i][0],&cord[i][1]);
    }

    int cur = 0,nxt;
    float min = 200000.0f,dis;
    for(int n0=1;n0<=n;n0++){
        scanf("%d",&nxt);
        dis = dist(cord[cur][0],cord[cur][1],cord[nxt][0],cord[nxt][1]);
        min = min < dis?min : dis;
        cur = nxt;
    }//少了最后回到原点的一段
    nxt = 0;
    dis = dist(cord[cur][0],cord[cur][1],cord[nxt][0],cord[nxt][1]);
    min = min < dis?min : dis;
    printf("%.2f\n",min);
    return 0;
}