#include <iostream>
#include <cstring>
#include "CMyStack.h"
#include "MyCharAppender.h"//自定义了一个类，用于处理形如12.34的输入
using namespace std;
class CExpression
{
private:
    char *s;
    int slen;
    CMyStack <char>opt;
    CMyStack <double>num;

    int precede(char c){
        if(c=='+'||c=='-')return 2;
        if(c=='*'||c=='/')return 3;
        if(c=='#')return 0;
        if(c=='(')return 1;
        if(c==')')return 8;
        return -1;
    }
    void CalcAndPushNum(double num1,char theta,double num2){//不改变opt栈，改变num栈，需要提前读出运算符
        if(theta=='+'){
            num.push(num1+num2);
        }else if(theta=='-'){
            num.push(num1-num2);
        }else if(theta=='*'){
            num.push(num1*num2);
        }else if(theta=='/'){
            num.push(num1/num2);
        }
    }

public:
    CExpression(const char input[]=""){SetExpression(input);}
    ~CExpression(){delete s;}
    void SetExpression(const char input[]){//update s[] and slength
        slen=strlen(input);
        s=new char[slen+2];
        strcpy(s+1,input);
        s[0]='#';
        s[slen+1]='#';
    }
    double Value(){//假设s已经是"#a+b*(c+d)#"",s[0]=s[slen+1]='#',s[1]=first char ,s[len]=last char.
        if(slen==0)return 0;
        opt.clear();
        num.clear();
        CharAppender curNumBuilder;
        for(int i=0;i<slen+2;i++){
            char c=s[i];
            if(('0'<=c&&c<='9'||c=='.')){
                 // 持续读取一个数值的各个字符
                curNumBuilder.append(c);
            }else{
                // Step1.如果追加器有值，说明之前读取的字符是数值，而且此时已经完整读取完一个数值,压入数字栈
                if(!curNumBuilder.empty()){
                    num.push(curNumBuilder.toDouble());
                    curNumBuilder.clear();
                }
                //Step2. 当前c为符号，做正常判断
                if(opt.empty()){
                    // 运算符栈栈顶为空则直接入栈
                    opt.push(c);
                }else{
                    if(c=='('){
                        // 当前运算符为左括号，直接入运算符栈
                        opt.push(c);
                    }else if(c==')'){
                        // 当前运算符为右括号，触发括号内的字表达式进行计算
                        while (opt.peek()!='('){
                            double num2=num.peek();num.pop();
                            double num1=num.peek();num.pop();
                            char optchar=opt.peek();opt.pop();
                            CalcAndPushNum(num1,optchar,num2);
                        }
                        //此时符号栈顶为'('
                        opt.pop();
                    }else{
                        // 当前运算符为加减乘除之一，要与栈顶运算符比较，判断是否要进行一次二元计算
                        if(precede(c)>precede(opt.peek())){
                            //仍能保持opt栈内递增优先级
                            opt.push(c);
                        }else{
                            while(precede(c)<=precede(opt.peek())&&opt.size()>=2){//opt.size()>=2是为了防止c='#'且栈内只有‘#’的时候多进行一次运算
                                double num2=num.peek();num.pop();
                                double num1=num.peek();num.pop();
                                char optchar=opt.peek();opt.pop();
                                CalcAndPushNum(num1,optchar,num2);
                            }
                            //此时c压入不会引起符号混乱
                            opt.push(c);
                        }
                    }
                }
            }
        }
        return num.peek();
    }
    
};



int main(){
    char s[100];
    CExpression expr;

    cin>>s;
    expr.SetExpression(s);
    cout<<expr.Value()<<endl;

    return 0;
}