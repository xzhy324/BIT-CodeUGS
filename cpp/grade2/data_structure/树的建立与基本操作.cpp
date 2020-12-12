#include "iostream"
#include "string"
using namespace std;
#define N 1000
struct CSTree{
    char data;
    CSTree *first_child,*next_sibling;
};
int degree[N]={0};
string head(string input){
    if(input.size()==1)return input;
    input=input.substr(1,input.size()-2);
    int bracket=0;
    for(auto i=input.begin();i<input.end();i++){
        if(*i=='(')bracket++;
        if(*i==')')bracket--;
        if(*i==','&&bracket==0){
            input=input.substr(0,i-input.begin());
            break;
        }
    }
    return input;
}
string tail(string input){
    input=input.substr(1,input.size()-2);
    int bracket=0,no_comma=1;
    auto i=input.begin();
    for(;i<input.end();i++){
        if(*i=='(')bracket++;
        if(*i==')')bracket--;
        if(*i==','&&bracket==0){
            input=input.substr(i-input.begin()+1,input.size());
            no_comma=0;
            break;
        }
    }
    if(i==input.end()&&no_comma)input.clear();
    input.insert(input.begin(),'(');
    input.insert(input.end(),')');
    return input;
}
void CreateTree(CSTree* curTree,const string& L){
    int curTree_degree=0;
    curTree->data=*(head(L).begin());//树根
    curTree->next_sibling= nullptr;
    curTree->first_child= nullptr;
    if(tail(L)!="()"){//子树
        string curHead=head(tail(L));
        curTree_degree++;
        string curTail=tail(tail(L));
        curTree->first_child= new CSTree;
        CreateTree(curTree->first_child,curHead);
        CSTree* p=curTree->first_child;
        while(curTail!="()"){
            curHead=head(curTail);
            curTree_degree++;
            curTail=tail(curTail);
            p->next_sibling=new CSTree;
            CreateTree(p->next_sibling,curHead);
            p=p->next_sibling;
        }
        p->next_sibling= nullptr;
    }
    degree[curTree_degree]++;
}
void printTree(CSTree* curTree,int layer){
    if(curTree == nullptr)return;
    for(int i=1;i<=4*(layer-1);i++)printf(" ");
    printf("%c\n",curTree->data);
    printTree(curTree->first_child,layer+1);
    printTree(curTree->next_sibling,layer);
}
int main(){
    string input;
    cin>>input;
    if(input=="()"){
        printf("Degree of tree: 0\nNumber of nodes of degree 0: 0\n");
        return 0;
    }
    auto *T = new CSTree;
    CreateTree(T,input);
    printTree(T,1);
    int n_max;
    for(n_max=N-1;n_max>=0&&degree[n_max]==0;n_max--);
    printf("Degree of tree: %d\n",n_max);
    for(int i=0;i<=n_max;i++)printf("Number of nodes of degree %d: %d\n",i,degree[i]);
    return 0;
}