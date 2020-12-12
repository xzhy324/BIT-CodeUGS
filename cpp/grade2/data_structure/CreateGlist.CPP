#include "cstdio"
#include "cstring"
#include "cstdlib"
#define N 10000
typedef enum {ATOM=0,LIST}ElemTag;
struct GLNode{
    ElemTag tag;
    union{
        char atom;
        struct{
            GLNode* head;
            GLNode* tail;
        }ptr;
    };
};
typedef GLNode* GList;
typedef char* SString;
void SubString(SString sub,char s[]){
    int slen=strlen(s);
    for(int i=1;i<=slen-2;i++)sub[i-1]=s[i];
    sub[slen-2]=0;
    return;
}
void sever(SString sub,SString hsub){
    int slen=strlen(sub);
    int right_bracket=0,hpoint;
    for(int i=0;i<=slen;i++){//detect hsub[]
        if(sub[i]=='(')right_bracket++;
        if(sub[i]==')')right_bracket--;
        if(right_bracket==0&&(sub[i]==','||i==slen)){
            hpoint=i;
            break;
        }
    }
    for(int i=0;i<=hpoint-1;i++){//create hsub[]
        hsub[i]=sub[i];
    }
    for(int i=hpoint+1;i<=slen;i++){//change sub[]
        sub[i-hpoint-1]=sub[i];
    }
    return;
}
bool CreateGList( GList &L, char *S )// 根据字符串 S 表示的广义表内容建立广义表数据结构；
{
    if(strcmp(S,"()")==0)L=NULL;
    else if(strlen(S)==1){
        L=(GList)malloc(sizeof(GLNode));
        L->tag=ATOM; L->atom=S[0];
    }else{
        L=(GList)malloc(sizeof(GLNode));
        L->tag=LIST;
        char sub[N];
        GList p=L;
        SubString(sub,S);
        do{
            char hsub[N];
            sever(sub,hsub);
            CreateGList(p->ptr.head,hsub);
            if(strlen(sub)!=0){
                p->ptr.tail=(GList)malloc(sizeof(GLNode));
                p->tag=LIST;
                p=p->ptr.tail;
            }
        }while(strlen(sub)!=0);
        p->ptr.tail=NULL;
    }
} 
GList GetHead( GList L)  // 取表头运算
{
    
}
GList GetTail( GList L)  // 取表尾运算
{

}
void DestroyGList( GList &L)  // 销毁广义表 L
{

}
void PrintGList( GList L) // 显示广义表 L 内容
{

}
int main(){
    printf("generic list\n");
    return 0;
}