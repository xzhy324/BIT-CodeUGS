#include <stdio.h>
#include <string.h>
int main() {
    char s[60];
    fgets(s, 60, stdin);
    int a[15]={0};
    int slen = strlen(s);
    for(int i = 0; i < slen; i++){
        if(s[i]>='2'&&s[i]<='9'){
            ++a[s[i]-'0'];
        }else if(s[i]=='A'){
            ++a[1];
        }else if(s[i]=='J'){
            ++a[11];
        }else if(s[i]=='Q'){
            ++a[12];
        }else if(s[i]=='K'){
            ++a[13];
        }else if(s[i]=='1'){
            ++i;
            ++a[10];
        }
    }

//    for(int i=1;i<=13;i++){
//        printf("%d ",a[i]);
//    }

    int ans = 0,current = 0;
    for(int i=1;i<=14;i++){
        if(a[i]==0){
            ans = ans > current ? ans : current;
            current = 0;
        }else{
            ++current;
        }
    }
    if(ans<=4){
        printf("DAMN\n");
    }else {
        printf("%d\n",ans);
    }
    return 0;
}