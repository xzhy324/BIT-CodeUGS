#include "iostream"
#include "cstring"
using namespace std;
enum STATE{q0,q1,q2,q3,q4,q5,q6,q7,q8};
enum TYPE{fuhao,dot,eE,num,others};
bool accept(STATE state){
    if(state==q2||state==q6||state==q7)return true;
    return false;
}
TYPE judge(char c){
    if('0'<=c&&c<='9')return num;
    if(c=='+'||c=='-')return fuhao;
    if(c=='.')return dot;
    if(c=='e'||c=='E')return eE;
    return others;
}
STATE next_state(STATE state, TYPE t){
    switch (state) {
        case q0:
            if(t==fuhao)return q3;
            if(t==num)return q2;
            return q1;
        case q1:
            return q1;
        case q2:
            if(t==num)return q2;
            if(t==dot)return q8;
            if(t==eE)return q4;
            return q1;
        case q3:
            if(t==num)return q2;
            return q1;
        case q4:
            if(t==num)return q7;
            if(t==fuhao)return q5;
            return q1;
        case q5:
            if(t==num)return q7;
            return q1;
        case q6:
            if(t==num)return q6;
            if(t==eE)return q4;
            return q1;
        case q7:
            if(t==num)return q7;
            return q1;
        case q8:
            if(t==num)return q6;
            return q1;
    }
}
int main(){
    int T;cin>>T;
    cin.get();
    while(T--){
        char s[1010];gets(s);
        int slen = strlen(s);

        int start = 0 , end = slen-1;
        while(s[start]==' ')start++;
        while(s[end]==' ')end--;
        if(start>end){
            cout<<"ILLEGAL\n";
            break;
        }

        STATE state=q0;
        for(int i=start;i<=end;i++){
            state = next_state(state,judge(s[i]));
        }

        if(accept(state)) cout<<"LEGAL\n";
        else cout<<"ILLEGAL\n";

    }
    return 0;
}