#include "iostream"
#include "cstring"
using namespace std;
class IntChar{
private:
    char* rawString;
    int n;
    void StringToInt();//将rawString转化为n
    void IntToString();//将n转为rawstring
    static char uncode(const int*,int,int);
public:
    IntChar(const char[]="");
    void SetNum(int);
    void INT();//print Int
    void Binary();//print Binary
    char At(int);
    static void PrintString(int);
};
char IntChar::uncode(const int *a,int start,int end){//将a转化为一个字符
        int max_p=end-start;
        char ans=0;
        for(int i=0;i<=max_p;i++){
            int cur=1;
            for(int j=1;j<=max_p-i;j++){
                cur*=2;
            }
            ans+=cur*a[start+i];
        }
        return ans;
    }
void IntChar::StringToInt (){//此时rawdata已经有值
    int bn[32];
    for(int i=0;i<4;i++){
        char c=rawString[i];
        for(int j=8*i+7;j>=8*i;j--){
            bn[j]=(int)c%2;
            c/=2;
        }
    }
    n=0;
    for(int i=0;i<32;i++){
        int cur=1;
        for(int j=1;j<=31-i;j++)
            cur*=2;
        n+=bn[i]*cur;
    }
}
void IntChar::IntToString (){//此时n已经有值,将n转为string
    int bn[32],n_copy=n;
    for(int i=31;i>=0;i--){
        bn[i]=n_copy%2;
        n_copy/=2;
    }
    for(int i=0;i<4;i++){
        rawString[i]=uncode(bn,8*i,8*i+7);
    }
}
IntChar::IntChar(const char input[]){//输入字符串，更新rawString与n
    rawString=new char[4];
    int length=strlen(input);
    if(length>=4){
        for(int i=0;i<4;i++){
        rawString[i]=input[i];
        }
    }else {
        for(int i=0;i<=3-length;i++)
            rawString[i]='\0';
        for(int i=4-length;i<4;i++)
            rawString[i]=input[i-(4-length)];
    }
    
    StringToInt();
}
void IntChar::SetNum(int inputNum){//输入整数，更新n与rawString
    n=inputNum;
    IntToString();
}
void IntChar::Binary(){//此时n已经有值
    int output[32],n_copy=n;
    for(int i=31;i>=0;i--){
        output[i]=n_copy%2;
        n_copy/=2;
    }
    for(int i=0;i<32;i++)printf("%d",output[i]);
    printf("\n");
}
void IntChar::INT(){//此时n已经有值
    printf("%d\n",n);
}
char IntChar::At(int Position){//此时rawString已经有值
    if(Position>=4)return '\0';
    int zero_cnt=0;
    for(int i=0;i<4;i++)
        if(rawString[i]=='\0')
            zero_cnt++;
    return rawString[zero_cnt+Position-1];
}
void IntChar::PrintString(int n_copy){
    int bn[32];
    for(int i=31;i>=0;i--){
        bn[i]=n_copy%2;
        n_copy/=2;
    }
    for(int i=0;i<4;i++){
        printf("%c",uncode(bn,8*i,8*i+7));
    }
    printf("\n");
}