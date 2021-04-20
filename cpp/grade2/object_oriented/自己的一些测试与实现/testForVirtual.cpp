#include "iostream"
using namespace std;
class item{
private:
    int id;
public:
    item(int input=0):id(input){cout<<"item constructed!\n";};
    ~item(){cout<<"item destructed!\n";};
};
class bookitem: public item{
private:
    char* title;
public:
    bookitem(int id=0,char* srcTitle="default"):item(id),title(srcTitle){
        cout<<"book constructed!\n";
    };
    ~bookitem(){cout<<"book destructed!\n";}
};

int main(){
    item *p;
    p= new bookitem;
    delete p;
    return 0;
}