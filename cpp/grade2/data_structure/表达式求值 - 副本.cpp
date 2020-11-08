#include "cstdio"
#include "stack"
#include "cmath"
#include "map"
#include "cstring"
#define add      '+'
#define minus    '-'
#define multiply '*'
#define divide   '/'
#define mod      '%'
#define exp      '^'
#define left     '('
#define right    ')'
#define send     '#'
const int N=1000;
const double epsilon=1e-8;
using namespace std;
stack<char> OP;stack<double> NUM;
void initStack()
{
    while(!OP.empty())OP.pop();
    while(!NUM.empty())NUM.pop();
}
char cmp2(char a,char b)
{
    if(a==add && b==add)return '>';if(a==add && b==minus)return '>';if(a==add && b==multiply)return '<';if(a==add && b==divide)return '<';if(a==add && b==mod)return '<';if(a==add && b==exp)return '<';if(a==add && b==left)return '<';if(a==add && b==right)return '>';if(a==add && b==send)return '>';
    if(a==minus && b==add)return '>';if(a==minus && b==minus)return '>';if(a==minus && b==multiply)return '<';if(a==minus && b==divide)return '<';if(a==minus && b==mod)return '<';if(a==minus && b==exp)return '<';if(a==minus && b==left)return '<';if(a==minus && b==right)return '>';if(a==minus && b==send)return '>';
    if(a==multiply && b==add)return '>';if(a==multiply&& b==minus)return '>';if(a==multiply && b==multiply)return '>';if(a==multiply && b==divide)return '>';if(a==multiply && b==mod)return '>';if(a==multiply && b==exp)return '<';if(a==multiply && b==left)return '<';if(a==multiply && b==right)return '>';if(a==multiply && b==send)return '>';
    if(a==divide && b==add)return '>';if(a==divide && b==minus)return '>';if(a==divide && b==multiply)return '>';if(a==divide && b==divide)return '>';if(a==divide && b==mod)return '>';if(a==divide && b==exp)return '<';if(a==divide && b==left)return '<';if(a==divide && b==right)return '>';if(a==divide && b==send)return '>';
    if(a==mod && b==add)return '>';if(a==mod && b==minus)return '>';if(a==mod && b==multiply)return '>';if(a==mod && b==divide)return '>';if(a==mod && b==mod)return '>';if(a==mod && b==exp)return '<';if(a==mod && b==left)return '<';if(a==mod && b==right)return '>';if(a==mod && b==send)return '>';
    if(a==exp && b==add)return '>';if(a==exp && b==minus)return '>';if(a==exp && b==multiply)return '>';if(a==exp && b==divide)return '>';if(a==exp && b==mod)return '>';if(a==exp && b==exp)return '<';if(a==exp && b==left)return '<';if(a==exp && b==right)return '>';if(a==exp && b==send)return '>';
    if(a==left && b==add)return '<';if(a==left && b==minus)return '<';if(a==left && b==multiply)return '<';if(a==left && b==divide)return '<';if(a==left && b==mod)return '<';if(a==left && b==exp)return '<';if(a==left && b==left)return '<';if(a==left && b==right)return '=';if(a==left && b==send)return 'E';
    if(a==right && b==add)return '>';if(a==right && b==minus)return '>';if(a==right && b==multiply)return '>';if(a==right && b==divide)return '>';if(a==right && b==mod)return '>';if(a==right && b==exp)return '>';if(a==right && b==left)return 'E';if(a==right && b==right)return '>';if(a==right && b==send)return '>';
    if(a==send && b==add)return '<';if(a==send && b==minus)return '<';if(a==send && b==multiply)return '<';if(a==send && b==divide)return '<';if(a==send && b==mod)return '<';if(a==send && b==exp)return '<';if(a==send && b==left)return '<';if(a==send && b==right)return 'E';if(a==send && b==send)return '=';
    return 'E';
}
void getNUM(char s[],int &spoint,double &num,int slen)
//1.从本位开始取连续的数字位，合成多位数  2.判断是否有减号需要结合为负号
{
    double atmp=s[spoint]-'0';
    int mark=spoint+1;
    while(mark<=slen-1&&'0'<=s[mark]&&s[mark]<='9')//多位数情况,先算小数位以前的部分
    {
        atmp=atmp*10+(s[mark]-'0');
        mark++;
    }

    if(mark<=slen-2&&s[mark]=='.')//若存在小数点
    {
        int mark0=mark;
        mark++;//越过小数位
        for(int i=mark0+1;i<=slen-1&&'0'<=s[i]&&s[i]<='9';i++)
        {
            atmp+=(double)(s[i]-'0')*pow(10,mark0-i);
            mark++;
        }   
    }
    num=atmp;

    if(spoint>=2)//[OP][-][num] 有减号需要结合情况
    {
        char c1,c2;
        c2=s[spoint-1];
        c1=s[spoint-2];
        if(c2=='-'&&!('0'<=c1&&c1<='9')&&c1)
        {
            OP.pop();
            num=-atmp;
        }  
    }
    spoint=mark;//移动下标
}
char getOP(char s[],int &spoint,double &num,int slen)
//若为OP，返回字符，若为数字，调用getNUM处理并移动光标，返回'N'说明num中数字更新
{
    if(spoint==slen)return '#';

    if('0'<=s[spoint]&&s[spoint]<='9')
    {
        getNUM(s,spoint,num,slen);
        return 'N';
    }
    spoint++;
    return s[spoint-1];
}
double operate(double a,char theta,double b)//注意a在右，b在左
{
    switch(theta)
    {
        case '+':
            return b+a;break;
        case '-':
            return b-a;break;
        case '*':
            return b*a;break;
        case '/':
            return b/a;break;
        case '%':
            return (int)b%(int)a;break;
        case '^':
            return pow(b,a);break;
    }
}
int check(double a,char theta,double b)//验证operate的合法性
{
    if(theta=='/'&&fabs(a-0.0)<epsilon)return 2;//divide 0
    if(theta=='^'&&a<0)return 3;//negative exp
    return 0;
}
int checkleft(char s[])//检查形如   ([OP]  或者  [OP])的非法情况，特别注意单个minus可以与后相邻数字结合
{
    int len=strlen(s);
    for(int i=0;i<=len-2;i++)
    {
        if(s[i]=='('&&
            (
            s[i+1]==')'||s[i+1]=='/'||s[i+1]=='*'||s[i+1]=='%' ||s[i+1]=='^'||
                (s[i+1]=='-' && !('0'<=s[i+2]&&s[i+2]<='9') )      
            )
        )
        return 1;
        if(s[i+1]==')'&&
            (
            s[i]=='('||s[i]=='/'||s[i]=='*'||s[i]=='%' ||s[i]=='^'||s[i]=='-'       
            )
        )
        return 1;
    }
    return 0;
}
int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        initStack();

        char s[N];
        s[0]='#';
        scanf("%s",s+1);
        
        int slen=strlen(s),spoint=1,errorFlag=0;
        double num;
        s[slen++]='#';s[slen]=0;
        errorFlag=checkleft(s);
        OP.push('#');
        char c=getOP(s,spoint,num,slen);
        while(!errorFlag&&(c!='#'||OP.top()!='#'))
        {
            if(c=='N')//number
            {
                NUM.push(num);
                c=getOP(s,spoint,num,slen);
            }
            else 
                switch(cmp2(OP.top(),c))
                {
                    case '<':
                        OP.push(c);
                        c=getOP(s,spoint,num,slen);
                        break;
                    case '=':
                        OP.pop();
                        c=getOP(s,spoint,num,slen);
                        break;
                    case '>':
                        if(spoint>=2&&c=='-')
                        {
                            if(!('0'<=s[spoint-2]&&s[spoint-2]<='9'))//[op][-][num],此时【-】不参与运算而寻求与后面数字结合
                            {
                                OP.push(c);//先压进去以便弹出来
                                c=getOP(s,spoint,num,slen);
                                break;
                            }
                        }
                        char theta;
                        theta=OP.top();OP.pop();
                        double x,y;
                        x=NUM.top();NUM.pop();
                        y=NUM.top();NUM.pop();
                        errorFlag=check (x,theta,y);
                        if(!errorFlag)NUM.push(operate(x,theta,y));
                        break;
                    case 'E':
                        errorFlag=1;
                        break;
                }
        } //while
        
        /*while(!OP.empty())
        {
            printf("%c ",OP.top());
            OP.pop();
        }
        printf("\n");
        while(!NUM.empty())
        {
            printf("%g ",NUM.top());
            NUM.pop();
        }*/

        if(OP.size()>1||NUM.size()>1)errorFlag=1;
        if(errorFlag==1)printf("error.\n");
        else if(errorFlag==2)printf("Divide 0.\n");
        else printf("%g\n",NUM.top());


    }//while(T--)
    return 0;
}