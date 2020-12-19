#include "iostream"
struct BSTree{
    int data;
    BSTree *lc,*rc;
};
bool SearchBST(BSTree *curTree,BSTree *parentTree,BSTree* &output,int key){
    if (curTree== nullptr){
        output=parentTree;
        return false;
    }else if(curTree->data==key){
        output=curTree;
        return true;
    }else{
        if(curTree->data<key)SearchBST(curTree->rc,curTree,output,key);
        else SearchBST(curTree->lc,curTree,output,key);
    }
    return false;
}
void InOrderTraverse(const BSTree *pTree) {
    if(pTree== nullptr)return;
    InOrderTraverse(pTree->lc);
    printf(" %d",pTree->data); 
    InOrderTraverse(pTree->rc);
}
void BookNotePrint(BSTree *pTree,int layer) {
    if(pTree== nullptr)return;
    BookNotePrint(pTree->lc,layer+1);
    for(int i=1;i<=4*(layer-1);i++)printf(" ");
    printf("%d\n",pTree->data);
    BookNotePrint(pTree->rc,layer+1);
}
int main(){
    auto *T=new BSTree;
    BSTree *buildNode;
    int key;
    scanf("%d",&key);
    T->data=key;
    T->rc= nullptr;T->lc= nullptr;
    while(key!=0){
        if(!SearchBST(T, nullptr,buildNode,key)){
            if(key<buildNode->data){
                buildNode->lc=new BSTree;buildNode=buildNode->lc;
                buildNode->data=key;
                buildNode->rc= nullptr;buildNode->lc= nullptr;
            }else{
                buildNode->rc=new BSTree;buildNode=buildNode->rc;
                buildNode->data=key;
                buildNode->rc= nullptr;buildNode->lc= nullptr;
            }
        }scanf("%d",&key);
    }
    BookNotePrint(T,1);
    printf("\n");InOrderTraverse(T);printf("\n");
    return 0;
}