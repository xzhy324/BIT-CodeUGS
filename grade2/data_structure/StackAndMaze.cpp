#include "cstdio"
#include "stack"
using namespace std;
const int maxn=110;
char maze[maxn][maxn];
struct PosType{
    int x,y;
};
struct elem{
    int order;
    PosType seat;
    int direction;//方向 1234对应下右上左
};
stack<elem>Path;
void initMaze(){
    for(int i=0;i<maxn;i++)
    for(int j=0;j<maxn;j++){
        maze[i][j]='1';
    }
}
void FootPrint(PosType curpos){//到访痕迹，即已经存在于Path中的点，为了求简单路径
    maze[curpos.x][curpos.y]='A';//'A' means Arrived
}
void BlockPrint(PosType curpos){//堵塞痕迹，即加入过Path又被弹出去的点，为了不死循环
    maze[curpos.x][curpos.y]='B';//'B' means Block
}
bool Pass(PosType curpos){
    if(maze[curpos.x][curpos.y]=='0')return true;
    return false;
}
bool PosEqual(PosType a,PosType b){
    if(a.x==b.x&&a.y==b.y)return true;
    return false;
}
PosType NextPos(PosType curpos,int direction){//对curpos关于方向改变
    switch(direction){
        case 1:curpos.x++;break;//down
        case 2:curpos.y++;break;//right
        case 3:curpos.x--;break;//up
        case 4:curpos.y--;break;//left
    }
    return curpos;
}
int main(){
    initMaze();
    int m,n;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            int tmp;scanf("%d",&tmp);
            maze[i][j]=tmp+'0';
        }
    PosType start={1,1};
    PosType end={n,n};
    PosType curPos = start;
    int curStep=1;
    do{
        if(Pass(curPos)){//当前位置可通，加入Path
            FootPrint(curPos);
            elem e;
            e.order=curStep;
            e.seat=curPos;
            e.direction=1;//从东开始
            Path.push(e);
            if(PosEqual(curPos,end))break;
            curPos=NextPos(curPos,1);//表示下一个位置是当前位置的南面
            curStep++;
        }else{//这个点走不过去，需要回溯
            if(!Path.empty()){
                elem e_pre=Path.top();
                Path.pop();
                 while(e_pre.direction==4&&!Path.empty()){//e_pre已经遍历完且Path中还有点
                    BlockPrint(e_pre.seat);
                    e_pre=Path.top();
                    Path.pop();
                }
                //接下来为还有方向未走的e_pre,且这个元素已经不在Path中，为挂起状态
                //注意若无出路时，（1，1）的direction会到5
                if(e_pre.direction<=3){
                    e_pre.direction++;//改变方向重新入栈
                    curPos=NextPos(e_pre.seat,e_pre.direction);
                    Path.push(e_pre);
                }
            }
        }
    }while(!Path.empty());
    if(!Path.empty()){

        /*printf("\n");
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                printf("%c ",maze[i][j]);
            }
        }
        printf("Step:%d\n",curStep);*/  //打印路径数以及路径

        stack<elem>output;
        while(!Path.empty()){
            output.push(Path.top());
            Path.pop();
        }
        while(!output.empty()){
            printf("<%d,%d> ",output.top().seat.x,output.top().seat.y);
            output.pop();
        }
        printf("\n");
    }else{
        printf("There is no solution!\n");
    }
    return 0;
}