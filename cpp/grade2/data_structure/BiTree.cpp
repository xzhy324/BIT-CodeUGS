#include "cstdio"
#include "cstring"
#include "cstdlib"
#define N 10000
struct BiTree{
    char data;
    BiTree *L_child;
    BiTree *R_child;
}T;
void BuildTree(char s[],int slen,int root,BiTree *Troot){
    if(root*2>slen){
        Troot->data=s[root];
        Troot->L_child=NULL;
        Troot->R_child=NULL;
        return;
    }
    if(root*2==slen){
        Troot->data=s[root];
        Troot->L_child=(BiTree*)malloc(sizeof(BiTree));
        BuildTree(s,slen,root*2,Troot->L_child);
        Troot->R_child=NULL;
        return;
    }
    if(root*2<slen){
        Troot->data=s[root];
        Troot->L_child=(BiTree*)malloc(sizeof(BiTree));
        Troot->R_child=(BiTree*)malloc(sizeof(BiTree));
        BuildTree(s,slen,root*2,Troot->L_child);
        BuildTree(s,slen,root*2+1,Troot->R_child);
        return;
    }
    return;
}
void PrintPreSequence(BiTree *Tree){
    if(Tree==NULL)return;
    else if(Tree->data=='#')return;
    printf("%c",Tree->data);
    PrintPreSequence(Tree->L_child);
    PrintPreSequence(Tree->R_child);
    return;
}
void PrintInSequence(BiTree *Tree){
    if(Tree==NULL)return;
    else if(Tree->data=='#')return;
    PrintInSequence(Tree->L_child);
    printf("%c",Tree->data);
    PrintInSequence(Tree->R_child);
    return;
}
void PrintPostSequence(BiTree *Tree){
    if(Tree==NULL)return;
    else if(Tree->data=='#')return;
    PrintPostSequence(Tree->L_child);
    PrintPostSequence(Tree->R_child);
    printf("%c",Tree->data);
    return;
}
void PrintBooknote(BiTree *curTree,int layer){
    if(curTree==NULL)return;
    else if(curTree->data=='#')return;
    for(int i=1;i<=4*(layer-1);i++)printf(" ");
    printf("%c\n",curTree->data);W
    PrintBooknote(curTree->L_child,layer+1);
    PrintBooknote(curTree->R_child,layer+1);
    return;
}
void LeaveAmount(BiTree *curTree,int &count){
    if(curTree==NULL)return;
    else if(curTree->data=='#')return;
    if(curTree->L_child==NULL&&curTree->R_child==NULL){
        count++;
        return;
    }else if(curTree->L_child==NULL&&curTree->R_child!=NULL){
        if(curTree->R_child->data=='#'){
            count++;
            return;
        }
    }else if(curTree->R_child==NULL&&curTree->L_child!=NULL){
        if(curTree->L_child->data=='#'){
            count++;
            return;
        }
    }else if(curTree->R_child!=NULL&&curTree->L_child!=NULL){
        if(curTree->L_child->data=='#'&&curTree->R_child->data=='#'){
            count++;
            return;
        }
    }
    LeaveAmount(curTree->L_child,count);
    LeaveAmount(curTree->R_child,count);
    return;
}
void SwapChild(BiTree *curTree){
    if(curTree==NULL)return;
    else if(curTree->data=='#')return;
    BiTree *tmp=curTree->L_child;
    curTree->L_child=curTree->R_child;
    curTree->R_child=tmp;
    SwapChild(curTree->L_child);
    SwapChild(curTree->R_child);
    return;
}
int main(){
    char s[N];
    scanf("%s",s);
    int slen=strlen(s);
    for(int i=slen;i>=1;i--)s[i]=s[i-1];
    BuildTree(s,slen,1,&T);
    printf("BiTree\n");
    PrintBooknote(&T,1);
    printf("pre_sequence  : ");
    PrintPreSequence(&T);
    printf("\nin_sequence   : ");
    PrintInSequence(&T);
    printf("\npost_sequence : ");
    PrintPostSequence(&T);
    printf("\n");
    int Leave=0;
    LeaveAmount(&T,Leave);
    printf("Number of leaf: %d\n",Leave);
    printf("BiTree swapped\n");
    SwapChild(&T);
    PrintBooknote(&T,1);
    printf("pre_sequence  : ");
    PrintPreSequence(&T);
    printf("\nin_sequence   : ");
    PrintInSequence(&T);
    printf("\npost_sequence : ");
    PrintPostSequence(&T);
    printf("\n");
    return 0;
}