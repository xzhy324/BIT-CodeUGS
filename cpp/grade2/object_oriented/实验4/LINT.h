#include "cstring"
#include "iostream"
class LINT{
private:
    static const int max_N=100;//最大输入字符串长度
    int *num;//倒序存储数据
    int length;//纯数字串长度
    char sub_title;
    static LINT minus(const int*,int,const int*,int);//前减后，两个数都是正数
    static LINT add(const int*,int,const int*,int,char);
public:
    LINT(const char* ="0");
    LINT Add(const LINT&);//achieve the sum of two big numbers
    void Print()const;//Print the value of LINT
};
LINT::LINT(const char* s){
    num=new int[max_N];
    if(s[0]=='+'||s[0]=='-'){
        sub_title=s[0];
        length=strlen(s)-1;
        for(int i=0;i<=length-1;i++)
            num[length-1-i]=s[i+1]-'0';
        for(int i=length;i<max_N;i++)num[i]=0;
    }else{
        sub_title='+';
        length=strlen(s);
        for(int i=0;i<=length-1;i++)
            num[length-1-i]=s[i]-'0';
        for(int i=length;i<max_N;i++)
            num[i]=0;
    }
}
LINT LINT::Add(const LINT& x){
    if(x.sub_title==sub_title){
        return add(x.num,x.length,num,length,sub_title);
    }else if(x.sub_title=='-'){
        return minus(num,length,x.num,x.length);
    }else return minus(x.num,x.length,num,length);
}
void LINT::Print()const{
    if(sub_title=='-')printf("-");
    for(int i=length-1;i>=0;i--){
        printf("%d",num[i]);
    }
    printf("\n");
}
LINT LINT::add(const int *a,int alen,const int *b,int blen,char op){//此时a和b是倒序放置高位补零的状态
    LINT result("0");
    result.sub_title=op;
    int bigger=alen>blen?alen:blen;	
    for(int i=0;i<=bigger;i++){
        if(result.num[i]+a[i]+b[i]<10)
            result.num[i]+=a[i]+b[i];
        else{
            result.num[i+1]++;result.num[i]+=a[i]+b[i]-10;
        }	
    }
    int no_zero=max_N-1;
    for(;no_zero&&!result.num[no_zero];no_zero--);
    if(no_zero<0){
        result.length=1;
        result.sub_title='+';
    }else{
        result.length=no_zero+1;
    }
    return result;
}
LINT LINT::minus(const int *a,int alen,const int*b,int blen){//a-b,且ab都是正数
    LINT result("0");
    bool a_is_larger=true;
    int bigger=alen>blen?alen:blen;
    for(int i=bigger-1;i>=0;i--){
        if(a[i]>b[i]){a_is_larger=true;break;}
        if(a[i]<b[i]){a_is_larger=false;break;}
    }
    if(a_is_larger)result.sub_title='+';
    else result.sub_title='-';
    const int *aa,*bb;//aa是更大的被减数
    if(a_is_larger){
        aa=a;bb=b;
    }else{
        aa=b;bb=a;
    }
    for(int i=0;i<=bigger-1;i++){
        if(aa[i]-bb[i]+result.num[i]>=0){
            result.num[i]+=aa[i]-bb[i];
        }else{
            result.num[i]+=10+aa[i]-bb[i];
            (result.num[i+1])--;
        }
    }
    int no_zero=max_N-1;
    for(;no_zero&&!result.num[no_zero];no_zero--);
    if(no_zero<0){
        result.length=1;
        result.sub_title='+';
    }else{
        result.length=no_zero+1;
    }
    return result;
}