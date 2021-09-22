#include "CMyStringV1.h"
class CSqlStatement{
private:
    CMyString sql_expression;
    int *Question_pos;//从【1】开始计算位置
    int Question_size;//统计问号个数
public:
    CSqlStatement(const char* input):sql_expression(input){//构造完成后找到了所有问号位置，更新了问号个数
        Question_size=0;
        for(int i=0;i<sql_expression.size();i++){
            if(sql_expression[i]=='?'){
                Question_size++;
            }
        }
        Question_pos=new int[Question_size+1];
        Question_size=0;
        for(int i=0;i<sql_expression.size();i++){//记录问号位置
            if(sql_expression[i]=='?'){
                Question_pos[++Question_size]=i;
            }
        }
    };
    bool SetAttribute(int Pos,const CMyString& input){//若设置失败，则不做任何更改并返回false
        if(Pos>Question_size)return false;//？个数不足

        if(Pos==1){
            if(!input.isNum())return false;

        }else if(Pos==2){
            for(int i=0;i<input.size();i++){//表名只含英文，数字，以及dot
                if(!(
                    (input[i]<='z'&&input[i]>='a')||
                    (input[i]<='Z'&&input[i]>='A')||
                    (input[i]<='9'&&input[i]>='0')||
                    input[i]=='.'
                ))return false;
            }

        }else if(Pos==3){
            if(!(input=="female")&&!(input=="male"))return false;

        }else if(Pos==4){
            if(!input.isNum())return false;

        }else if(Pos==5){
            for(int i=0;i<input.size();i++){
                if(!(
                        (input[i]<='z'&&input[i]>='a')||
                        (input[i]<='Z'&&input[i]>='A')||
                        (input[i]<='9'&&input[i]>='0')||
                        input[i]=='.'
                ))return false;
            }
        }
        sql_expression=
            sql_expression.Mid(0,Question_pos[Pos]-1)
            +input+
            sql_expression.Mid(Question_pos[Pos]+1,sql_expression.size()-1);

        for(int i=Pos+1;i<=Question_size;i++)//将之后所有的问号位置后移
            Question_pos[i]+=input.size()-1;
        return true;
    }

    void ExecuteSql(){cout<<sql_expression;}
};