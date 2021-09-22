#include "iostream"
#include "fstream"
#include "vector"
#include "cassert"
#include "cstring"
using namespace std;

vector<int> readLabel(string filename){
    vector<int> rtn ;
    ifstream ifs(filename.c_str(),ios::binary);
    char buf[1000];
    
}

int main(){
    FILE *fp = fopen(".\\t10k-labels.idx1-ubyte","r");
    if(!fp)cout<<"error";
    int num=1;
    for(int i=0;i<10;i++){
        fread(&num,sizeof(int),1,fp);
        cout<<num;
    }
    
}