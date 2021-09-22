#include "iostream"
//还可以改进的地方，由于scanInput接受一个字符然后转换成数字，因此只能接受节点数《=9的树
//若改成用%d接受，则会遇到scanf遗留\n至缓冲区从而判断不清楚，好办法是用字符串读入一行再处理这个串。
struct FC_BiTree{//data-孩子 数组表示法
    char data;
    int ln,rn;
}input1[30],input2[30];
int FindRoot(FC_BiTree input[],int n){
    for(int i=0;i<=n-1;i++)
        if(input[i].data=='A')return i;
    return -1;
}
int CountVoidChild(FC_BiTree *input){
    int ans=0;
    if(input->rn==-1)ans++;
    if(input->ln==-1)ans++;
    return ans;
}
void scanInput(FC_BiTree *input,int n){
    for(int i=0;i<=n-1;i++){
        getchar();
        scanf("%c %c %c",&(input+i)->data,&(input+i)->ln,&(input+i)->rn);
        if((input+i)->ln=='-')(input+i)->ln=-1;
        else (input+i)->ln -= '0';
        if((input+i)->rn=='-')(input+i)->rn=-1;
        else (input+i)->rn -= '0';
    }
}
bool judgeIsomorphism(int root1,int root2){
    if(input1[root1].data!=input2[root2].data)return false;
    else{//root data equals.
        int CVC1,CVC2;
        CVC1=CountVoidChild(input1+root1);
        CVC2=CountVoidChild(input2+root2);
        if(CVC1!=CVC2)return false;
        else if(CVC1==2)return true;
        else if(CVC1==1){
            if(input1[root1].rn==-1){
                if(input2[root2].rn==-1)
                    return judgeIsomorphism(input1[root1].ln,input2[root2].ln);
                else
                    return judgeIsomorphism(input1[root1].ln,input2[root2].rn);
            }else if(input1[root1].rn!=-1){
                if(input2[root2].rn==-1)
                    return judgeIsomorphism(input1[root1].rn,input2[root2].ln);
                else
                    return judgeIsomorphism(input1[root1].rn,input2[root2].rn);
            }
        }else if(CVC1==0){
            bool judgePair1,judgePair2;
            judgePair1=judgeIsomorphism(input1[root1].rn,input2[root2].rn)&&judgeIsomorphism(input1[root1].ln,input2[root2].ln);
            judgePair2=judgeIsomorphism(input1[root1].rn,input2[root2].ln)&&judgeIsomorphism(input1[root1].ln,input2[root2].rn);
            return judgePair1||judgePair2;
        }
    }
    return false;
}
int main(){
    int n,m;
    scanf("%d",&n);
    scanInput(input1, n);
    getchar();
    scanf("%d",&m);
    scanInput(input2,m);
    if(judgeIsomorphism(FindRoot(input1,n),FindRoot(input2,m)))
        printf("Yes.\n");
    else printf("No.\n");
    return 0;
}