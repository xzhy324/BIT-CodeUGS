#include "iostream"
#include "cstring"
struct BSTree{
    char data;
    BSTree *lc,*rc,*parent;//采用三叉链表存储
    int height;
};
void SearchTree(BSTree* Tree,BSTree* parentTree,char key,BSTree* &output);
int getHeight(BSTree *pTree){
    if(pTree== nullptr)return 0;
    else return pTree->height;
}
int getBalanceFactor(BSTree *pTree){//定义为左子树高度减去右子树高度
    if(pTree== nullptr)return 0;
    return getHeight(pTree->lc)-getHeight(pTree->rc);
}
int maxNum(int a,int b){return a>b?a:b;}
void updateHeight(BSTree *curTree){
    if(curTree== nullptr)return;
    else{
        int height_l=getHeight(curTree->lc);
        int height_r=getHeight(curTree->rc);
        curTree->height = maxNum(height_l,height_r)+1 ;
    }
}
BSTree *RRrotate(BSTree *pTree) {
    BSTree* dad=pTree->parent;
    BSTree* son=pTree->rc;
    if(son->lc!= nullptr)son->lc->parent=pTree;
    pTree->rc=son->lc;
    updateHeight(pTree);
    son->lc=pTree;
    son->parent=dad;
    if(dad!= nullptr){//更新爷爷节点的正确儿子
        if(dad->rc==pTree)dad->rc=son;
        else dad->lc=son;
    }
    pTree->parent=son;
    updateHeight(son);
    return son;
}
BSTree *LLrotate(BSTree *pTree) {
    BSTree* dad=pTree->parent;
    BSTree* son=pTree->lc;
    if(son->rc!= nullptr)son->rc->parent=pTree;
    pTree->lc=son->rc;
    updateHeight(pTree);
    son->rc=pTree;
    son->parent=dad;
    if(dad!= nullptr){//更新爷爷节点的正确儿子
        if(dad->rc==pTree)dad->rc=son;
        else dad->lc=son;
    }
    pTree->parent=son;
    updateHeight(son);
    return son;
}
BSTree *RLrotate(BSTree *pTree) {
    LLrotate(pTree->rc);
    return RRrotate(pTree);
}
BSTree *LRrotate(BSTree *pTree) {
    RRrotate(pTree->lc);
    return LLrotate(pTree);
}
BSTree* balance(BSTree* &curRoot, BSTree* curTree){//curRoot是整棵树的根，curTree为插入位置，while循环调整至最近最近失衡祖先，返回值为新的根（如果有调整）
    int cur_balance_factor;
    while(curTree!= nullptr){
        updateHeight(curTree);
        cur_balance_factor=getBalanceFactor(curTree);
        if(cur_balance_factor<=-2||cur_balance_factor>=2){
            if(cur_balance_factor<=-2){//右子树太重
                if(getBalanceFactor(curTree->rc)<0)curTree=RRrotate(curTree);//RR型，右子树的右孩子太重
                else curTree=RLrotate(curTree);//RL型
            }else if(cur_balance_factor>=2){
                if(getBalanceFactor(curTree->lc)>0)curTree=LLrotate(curTree);//LL
                else curTree=LRrotate(curTree);//LR
            }
            if(curTree->parent== nullptr){//到达根节点
                curRoot=curTree;break;
            }
        }
        curTree=curTree->parent;
    }
    return curRoot;
}
BSTree* Insertion(BSTree* &curTree,char input){
    BSTree *insertNode= new BSTree;
    insertNode->height=1;insertNode->rc= nullptr;insertNode->lc= nullptr;insertNode->data=input;
    BSTree* father;
    SearchTree(curTree, nullptr,input,father);
    if(input>father->data)father->rc=insertNode;
    else father->lc=insertNode;
    insertNode->parent=father;
    updateHeight(father);
    curTree = balance(curTree,father);
    return curTree;
}
void SearchTree(BSTree* Tree,BSTree* parentTree,char key,BSTree* &output){
    if(Tree== nullptr){
        output=parentTree;
        return;
    }else if(key>Tree->data)SearchTree(Tree->rc,Tree,key,output);
    else SearchTree(Tree->lc,Tree,key,output);
}
void InOrderTraverse(const BSTree *pTree) {
    if(pTree== nullptr)return;
    InOrderTraverse(pTree->lc);
    printf("%c",pTree->data);
    InOrderTraverse(pTree->rc);
}
void PreOrderTraverse(BSTree *pTree) {
    if(pTree== nullptr)return;
    printf("%c",pTree->data);
    PreOrderTraverse(pTree->lc);
    PreOrderTraverse(pTree->rc);
}
void PostOrderTraverse(BSTree *pTree) {
    if(pTree== nullptr)return;
    PostOrderTraverse(pTree->lc);
    PostOrderTraverse(pTree->rc);
    printf("%c",pTree->data);
}
void BookNotePrint(BSTree *pTree,int layer) {
    if(pTree== nullptr)return;
    BookNotePrint(pTree->rc,layer+1);
    for(int i=1;i<=4*(layer-1);i++)printf(" ");
    printf("%c\n",pTree->data);
    BookNotePrint(pTree->lc,layer+1);
}
int main(){
    char s[1000];scanf("%s",s);int slen=strlen(s);
    BSTree *T=new BSTree;
    T->parent= nullptr;T->height=1;T->lc= nullptr;T->rc= nullptr;T->data=s[0];
    for(int i=1;i<=slen-1;i++)T=Insertion(T,s[i]);
    printf("Preorder: ");PreOrderTraverse(T);printf("\n");
    printf("Inorder: "); InOrderTraverse(T);printf("\n");
    printf("Postorder: ");PostOrderTraverse(T);printf("\n");
    printf("Tree:\n"); BookNotePrint(T,1);
    return 0;
}