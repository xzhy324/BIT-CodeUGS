#include "iostream"
#include "cmath"
using namespace std;
class CMyString{
private:
    char *data;//规定所有字符串以\0结尾
    int length;

    static int getLen(const char* p){//获取字符串长度
        int result=0;
        while(*p!='\0'){p++;result++;}
        return result;
    }

    //比较s和p的前plen个字符
    static bool matched(const char* s,const char* p,int plen){
        bool res= true;
        for(int i=0;i<plen&&res;i++){
            res=(s[i]==p[i]);
        }
        return res;
    }
public:
    explicit CMyString(const char *input="");
    explicit CMyString (char);
    CMyString(const CMyString &);
    CMyString& operator =(const CMyString&);
    CMyString& operator =(const char*);
    friend ostream& operator <<(ostream& os,const CMyString& a);
    char& operator[](int _pos)const{return data[_pos];}
    double ToDouble()const;
    double ToInt()const;
    int Find(const CMyString&)const;
    int Find(char)const;
    int Find(const char*)const;
    int FindBackwards(char)const;
    CMyString Mid(int start,int end);
    CMyString operator +(const CMyString&)const;
    CMyString operator +(const char*)const;
    CMyString operator +(char)const;
    friend CMyString operator +(const char*,const CMyString&);
    CMyString operator -(const CMyString&)const;
    CMyString operator -(const char *)const;
    CMyString operator -(char)const;
    int size()const{return length;}
};

ostream& operator <<(ostream& os,const CMyString& a){
    os<<a.data;
    return os;
}

CMyString::CMyString(const char *input) {
    length=getLen(input);
    data =new char[length+1];
    for(int i=0;i<length;i++){
        data[i] = input[i];
    }data[length]=0;
}

CMyString::CMyString(char input) {
    data=new char[2];
    data[0]=input;
    data[1]='\0';
    length=1;
}

CMyString::CMyString(const CMyString &input) {
    data=new char[input.length+1];
    length=input.length;
    for(int i=0;i<length;i++)
        data[i]=input.data[i];
    data[length]= '\0';
}

CMyString& CMyString::operator=(const CMyString &input) {
    if(this!=&input){
        data=new char[input.length+1];
        length=input.length;
        for(int i=0;i<length;i++)
            data[i]=input.data[i];
        data[length]='\0';
    }
    return *this;
}

CMyString& CMyString::operator=(const char *input) {
    length=getLen(input);
    data=new char[length+1];
    for(int i=0;i<length;i++)
        data[i]=input[i];
    data[length]='\0';
    return *this;
}

double CMyString::ToDouble() const {
    double result=0;
    if(length==0)return 0;
    int commaPosition=0;//找到小数点位置
    for(int i=0;i<length;i++){
        if(data[i]=='.'){
            commaPosition=i;
            break;
        }
    }
    if(commaPosition==0){//无小数点情况
        for(int i=length-1;i>=0;i--){
            result+=pow(10,length-i-1)*(data[i]-'0');
        }
    }else{//有小数点情况，分两部分加
        for(int i=commaPosition-1;i>=0;i--){
            result+=pow(10,commaPosition-i-1)*(data[i]-'0');
        }
        for(int i=commaPosition+1;i<length;i++){
            result+=pow(10,-i+commaPosition)*(data[i]-'0');
        }
    }
    return result;
}

double CMyString::ToInt() const {
    return (int)ToDouble();
}

CMyString CMyString::Mid(int start, int end) {
    CMyString result;
    result.length=end-start+1;
    result.data=new char[result.length+1];
    for(int i=start;i<=end;i++){
        result.data[i-start]=data[i];
    }result.data[end+1]='\0';
    return result;
}

CMyString CMyString::operator + (const CMyString &input) const {
    CMyString result;
    result.length=this->length+input.length;
    result.data=new char[result.length+1];
    for(int i=0;i< this->length;i++)
        result.data[i]=this->data[i];
    for(int i= this->length;i<result.length;i++)
        result.data[i]=input.data[i- this->length];
    result.data[result.length]='\0';
    return result;
}

CMyString CMyString::operator + (const char* input)const{
    CMyString res;
    int input_length=getLen(input);
    res.length=this->length+input_length;
    res.data=new char[res.length+1];
    for(int i=0;i<length;i++)
        res.data[i]=this->data[i];
    for(int i=length;i<res.length;i++)
        res.data[i]=input[i-length];
    res.data[res.length]='\0';
    return res;
}

CMyString CMyString::operator + (char c)const{
    CMyString res;
    res.length=length+1;
    res.data=new char[res.length+1];
    for(int i=0;i<res.length-1;i++)
        res.data[i]=data[i];
    res.data[res.length-1]=c;
    res.data[res.length]='\0';
    return res;
}

CMyString operator + (const char *srcChar, const CMyString &srcString) {
    return CMyString(srcChar)+srcString;
}

int CMyString::Find(const CMyString &pat) const {
    int res=-1;
    for(int i=0;i<=length-pat.length;i++){
        if(matched(data+i,pat.data,pat.length)){
            res=i;
            break;
        }
    }
    return res;
}

int CMyString::Find(char c) const {
    int res=-1;
    for(int i=0;i<length;i++){
        if(data[i]==c){
            res=i;
            break;
        }
    }
    return res;
}

int CMyString::Find(const char *input) const {
    int res=-1;
    int input_length=getLen(input);
    for(int i=0;i<=length-input_length;i++){
        if(matched(data+i,input,input_length)){
            res=i;
            break;
        }
    }
    return res;
}

int CMyString::FindBackwards(char c) const {
    int res=-1;
    for(int i=length-1;i>=0;i--)
        if(data[i]==c){
            res=i;
            break;
        }
    return res;
}

CMyString CMyString::operator-(const CMyString &pat) const {
    char *tmp = new char[length+1];
    int tmp_length=0;
    int i;
    for(i=0;i<=length-pat.length;i++){
        if(matched(data+i,pat.data,pat.length)){
            i+=pat.length;
            i--;
        }else{
            tmp[tmp_length++]=data[i];
        }
    }
    while(i<=length-1){//将最后不足一个串的部分补进去
        tmp[tmp_length++]=data[i];
        i++;
    }
    tmp[tmp_length]='\0';
    return CMyString(tmp);
}

CMyString CMyString::operator-(const char *input) const {
    char *tmp = new char[length+1];
    int input_length=getLen(input);
    int tmp_length=0;
    int i;
    for(i=0;i<=length-input_length;i++){
        if(matched(data+i,input,input_length)){
            i+=input_length;
            i--;
        }else{
            tmp[tmp_length++]=data[i];
        }
    }
    while(i<=length-1){//将最后不足一个串的部分补进去
        tmp[tmp_length++]=data[i];
        i++;
    }
    tmp[tmp_length]='\0';
    return CMyString(tmp);
}

CMyString CMyString::operator-(char c) const {
    char tmp[2]={c,'\0'};
    return *this - tmp;
}