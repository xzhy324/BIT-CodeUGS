
#include "cmath"
class CharAppender{
public:
    CharAppender(int user_size=10){
        s=new char[user_size];
        max_size=user_size;
        length=0;
    }
    bool empty(){
        if(length>0)return false;return true;
        }
    void append(char c){
        if(length<max_size)s[length++]=c;
        }
    void clear(){
        length=0;
        }
    double toDouble(){
        double result=0;
        if(length==0)return 0;
        int commaPosition=0;//找到小数点位置
        for(int i=0;i<length;i++){
            if(s[i]=='.'){
                commaPosition=i;
                break;
            }
        }
        if(commaPosition==0){//无小数点情况
            for(int i=length-1;i>=0;i--){
                result+=pow(10,length-i-1)*(s[i]-'0');
            }
        }else{//有小数点情况，分两部分加
            for(int i=commaPosition-1;i>=0;i--){
                result+=pow(10,commaPosition-i-1)*(s[i]-'0');
            }
            for(int i=commaPosition+1;i<length;i++){
                result+=pow(10,-i+commaPosition)*(s[i]-'0');
            }
        }
        return result;
    }
private:
    char* s;
    int max_size;
    int length;
};