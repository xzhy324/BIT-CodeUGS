#include "iostream"
#include "cstring"
#define N 200
struct link{
    char *end;
    int endNum;
    link(){
        end=new char[N];
        endNum=0;
    };
}graph[N];
int n=0;   int max[27]={0},min[27]={0},input[27]={0};
void dfs(char cur_ch) {
    if(graph[cur_ch].endNum==0){
        max[cur_ch-'a']=1;
        return;
    }
    for(int i=0;i<graph[cur_ch].endNum;i++)
        dfs(graph[cur_ch].end[i]);
}
int main(){
    char s[N];scanf("%s",s);int slen=strlen(s);
    for(int i=0;i<slen;i+=2){
        input[s[i]-'a']=1;
        min[s[i]-'a']=1;
        n++;
    }
    scanf("%s",s);slen=strlen(s);
    for(int i=1;i<slen;){
        int endPos=graph[s[i]].endNum;
        graph[s[i]].end[endPos]=s[i+2];
        min[s[i+2]-'a']++;//>=2说明不是极小值
        (graph[s[i]].endNum)++;
        i+=6;
    }
    char outputmin[27];int n_min=0;
    for(int i=0;i<n;i++)if(min[i]==1)outputmin[n_min++]=i+'a';
    for(int i=0;i<n_min-1;i++)printf("%c,",outputmin[i]);
    printf("%c\n",outputmin[n_min-1]);

    for(int i='a';i<='z';i++){
        if(input[i-'a']==0)continue;
        dfs(i);
    }
    char outputmax[27];int n_max=0;
    for(int i=0;i<n;i++)if(max[i]==1)outputmax[n_max++]=i+'a';
    for(int i=0;i<n_max-1;i++)printf("%c,",outputmax[i]);
    printf("%c\n",outputmax[n_max-1]);
    return 0;
}