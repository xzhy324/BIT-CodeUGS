#include "cstdio"
#include "stack"
#include "map"
#include "cstring"
using namespace std;
map<char,int>priority;
stack<char>op;
void initMap(){
    priority['#']=0;
    priority['(']=1;
    priority['+']=2;
    priority['-']=2;
    priority['*']=3;
    priority['/']=3;
    priority['%']=3;
    priority['^']=4;
    priority[')']=5;
}
void initStack(){
    while(!op.empty())op.pop();
    op.push('#');
}
bool isOP(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='^'||c=='('||c==')'||c=='#')return true;
    return false;
}
char cmp(char a,char b){//a is top of the stack OP
    auto pa=priority.find(a);
    auto pb=priority.find(b);
    int delta=pa->second - pb->second;
    if(a=='^'&&b=='^')return '<';
    if(delta>=0)return '>';
    return '<';
}
int main(){
    initMap();
    int N;scanf("%d",&N);
    while(N--){
        char s[1000];scanf("%s",s);
        int slen=strlen(s),num;
        initStack();
        for(int i=0;i<=slen-2;i++){
            char c=s[i];
            if(!isOP(c)){//数字或者字母
                printf("%c",c);
            }else if(c=='('){//左右括号单独处理
                op.push(c);
            }else if(c==')'){
                while(op.top()!='('){
                    printf("%c",op.top());
                    op.pop();
                }
                if(op.top()=='(')op.pop();
            }else{//算符
                switch(cmp(op.top(),c)){
                    case '<':
                        //先判断是否为负号
                        if((i>=1&&c=='-'&&isOP(s[i-1])&&s[i-1]!=')')||(i==0&&c=='-')){
                            printf("-");
                            break;
                        }
                        //这里开始正常处理
                        op.push(c);break;
                    case '>':
                        //先判断是否为负号
                        if((i>=1&&c=='-'&&isOP(s[i-1])&&s[i-1]!=')')||(i==0&&c=='-')){
                            printf("-");
                            break;
                        }
                        //这里开始正常处理
                        while(!op.empty()&&cmp(op.top(),c)=='>'){
                            printf("%c",op.top());
                            op.pop();
                        }
                        if(!op.empty()&&cmp(op.top(),c)=='<')op.push(c);
                        break;
                }//switch
            }//if
        }//for
        while(!op.empty()&&op.top()!='#'){
            printf("%c",op.top());
            op.pop();
        }
        printf("\n");
    }
    return 0;
}