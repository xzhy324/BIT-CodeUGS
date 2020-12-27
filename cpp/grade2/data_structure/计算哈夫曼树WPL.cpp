#include "iostream"
#define MAX 0x3f3f3f3f
typedef struct {
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
int WPL=0;
void Select(HuffmanTree &HT, int i,int &s1,int &s2){
    unsigned int flag = MAX;
    for (int j=1;j<=i;j++){
        if (HT[j].parent==0 && HT[j].weight<flag){
            s1=j;
            flag=HT[j].weight;
        }
    }flag = MAX;
    for (int j=1;j<=i;j++){
        if (HT[j].parent==0 && HT[j].weight<flag && j!=s1){
            s2=j;
            flag=HT[j].weight;
        }
    }
}
void CreateHuffmanTree(HuffmanTree &HT, unsigned int *w, int n){
    //w为n个权值，构造哈夫曼树，并求出n个字符的哈夫曼编码
    if(n<=1)return;
    int m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof (HTNode));//unit 0 is not used
    HuffmanTree p=HT+1;
    int i;
    for(i=1;i<=n;i++,p++,w++)*p={*w,0,0,0};
    for(;i<=m;i++)*p={0,0,0,0};
    for(i=n+1;i<=m;i++){//建哈夫曼树
        int s1,s2;//在HT[1...i-1]中选择parent为0且weight最小的两个节点,其序号为s1，s2
        Select(HT,i-1,s1,s2);
        HT[s1].parent=i;HT[s2].parent=i;
        HT[i].lchild=s1;HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
        WPL+=HT[i].weight;
    }
}
int main(){
    HuffmanTree tree;
    int n;unsigned int w[1000];
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&w[i]);
    CreateHuffmanTree(tree,w,n);
    printf("WPL=%d\n",WPL);
}