#include "iostream"
#include "cstring"
#include "stack"
#define N 1000
using namespace std;
char input[N];
int trueTable[N];
char elemTable[N];
int m[N];//1表示对应mi在最后的析取式中，0表示不在结果中
int elemNum,pow2ElemNUM;
stack<char>OP;stack<char>VALUE;
int cmp(char c){
    switch (c) {
        case '!':return 5;
        case '|':return 4;
        case '&':return 3;
        case '-':return 2;
        case '+':return 1;
        case ')':return 6;
        case '(':return 0;
        default:return -1;
    }
}
void ElemStat() {
    int slen=strlen(input);
    elemNum=0;
    for(int i=0;i<slen;i++)if(input[i]>='a'&&input[i]<='z'){
            if(elemNum==0){
                elemTable[elemNum++]=input[i];
            }else{
                int find=0;
                for(int j=0;j<elemNum&&!find;j++){
                    if(elemTable[j]==input[i])find=1;
                }
                if(!find)elemTable[elemNum++]=input[i];
            }
        }
}
void changeTrueTable(int x){
    for(int i=0;i<elemNum;i++){
        trueTable[i]=x%2;
        x/=2;
    }
}
int pow2(int num) {
    int result=1;
    for(int i=1;i<=num;i++)result*=2;
    return result;
}
int getOrder() {
    int result=0;
    for(int i=0;i<elemNum;i++){
        result+=pow2(elemNum-i-1)*trueTable[i];
    }
    return result;
}
char solve(char left,char op,char right){
    int a,b,result;
    if(left=='T')a=1;else a=0;
    if(right=='T')b=1;else b=0;
    switch (op) {
        case '!':result=!b;VALUE.push(left);break;
        case '&':result=a&&b;break;
        case '|':result=a||b;break;
        case '+':result=(a==b);break;
        case '-':result=(!a)||b;break;
        default:result=0;
    }
    if(result==1)return 'T';
    return 'F';
}
int findELem(char key) {
    for(int i=0;i<elemNum;i++){
        if(key==elemTable[i])return i;
    }
    return 0;
}
int judge() {//返回0表示这组赋值使得原命题为假，返回1表示这组赋值使原命题为真
    char s[N];strcpy(s,input);
    int slen=strlen(s);

    for(int x=0;x<slen;x++){
        if('a'<=s[x]&&s[x]<='z'){
            int order=findELem(s[x]);
            if(trueTable[order]==1)s[x]='T';
            else s[x]='F';
        }
    }//预处理整个串,替换变元到具体的赋值
    while(!OP.empty())OP.pop();//置空初始化
    while(!VALUE.empty())VALUE.pop();//置空初始化
    VALUE.push('#');

    for(int i=0;i<slen;i++){
        if(s[i]=='T'||s[i]=='F'){
            VALUE.push(s[i]);
        }else if(s[i]==')'){//右括号情形
            while(OP.top()!='('){
                char op   =OP.top();OP.pop();
                char right=VALUE.top();VALUE.pop();
                char left =VALUE.top();VALUE.pop();
                VALUE.push(solve(left,op,right));
            }
            OP.pop();//弹出左括号
        }else if(s[i]=='('){//左括号情形
            OP.push('(');
        }else{//其他可操作算符//先计算后压入结果，再压入算符
            while(VALUE.size()>=2&&!OP.empty()&&cmp(OP.top())>cmp(s[i])){
                char right=VALUE.top();VALUE.pop();
                char left =VALUE.top();VALUE.pop();
                char op   =OP.top();OP.pop();
                VALUE.push(solve(left,op,right));
            }
            OP.push(s[i]);
        }
    }
    while(!OP.empty()){
        char right=VALUE.top();VALUE.pop();
        char left =VALUE.top();VALUE.pop();
        char op   =OP.top();OP.pop();
        VALUE.push(solve(left,op,right));
    }//没有括号之后一起算
    if (VALUE.top()=='T')return 1;
    return 0;
}
void mPrint() {
    int mark=0,output[N];
    for(int i=0;i<pow2ElemNUM;i++){
        if(m[i]==1)output[mark++]=i;
    }
    if(mark==0)printf("0");
    else{
        for(int i=0;i<mark-1;i++){
            printf("m%d ∨ ",output[i]);
        }printf("m%d",output[mark-1]);
    }
}
void MPrint(){
    int mark=0,output[N];
    for(int i=0;i<pow2ElemNUM;i++){
        if(m[i]==0)output[mark++]=i;
    }
    if(mark==0)printf("1");
    else{
        for(int i=0;i<mark-1;i++){
            printf("M%d ∧ ",output[i]);
        }printf("M%d",output[mark-1]);
    }
}
int main(){
    scanf("%s",input);
    ElemStat();
    pow2ElemNUM=pow2(elemNum);
    for(int i=0;i<pow2ElemNUM;i++){
        changeTrueTable(i);
        m[getOrder()]=judge();
    }
    mPrint();printf(" ; ");
    MPrint();printf("\n");
    return 0;
}