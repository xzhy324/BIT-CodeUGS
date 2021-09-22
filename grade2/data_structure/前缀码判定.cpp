# include "iostream"
# include "cstring"
using namespace std;
typedef struct node{
    struct node *left,*right;
}Node,*Tree;
bool UpdateTree(Tree tree, char s[])
{
    int slen=strlen(s);
    for(int i=0;i<slen;i++)
    {
        Node *tmp;
        if(s[i]=='0')tmp= tree->left;
        if(s[i]=='1')tmp= tree->right;
        if(i==slen-1&&tmp!=nullptr) return false;
        if(tmp!=nullptr&&tmp->left==nullptr&&tmp->right==nullptr&&i<slen)return false;
        if(tmp==nullptr)
        {
            tmp = new node;
            tmp->left = nullptr;
            tmp->right = nullptr;
            if(s[i]=='0') tree->left=tmp;
            else tree->right=tmp;
            tree = tmp;
        }
        else tree = tmp;
    }
    return true;
}
char s[200000];
int main()
{
    int n,flag=0;
    Tree tree = new node;
    tree->left=nullptr;tree->right=nullptr;
    cin>>n;
    for(int i=1;i<=n&&flag!=1;i++){
        scanf("%s",s);
        if(!UpdateTree(tree,s))flag=1;
    }
    if(flag==1) printf("%s\n",s);
    else printf("YES\n");
    return 0;
}