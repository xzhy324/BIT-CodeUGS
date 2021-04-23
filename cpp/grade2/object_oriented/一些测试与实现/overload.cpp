#include "iostream"
#include "cstring"
using namespace std;
class F{
private:
    double data;
    char *s;
public:
    double operator () (double a, double b){
        return a+b;
    }
    operator int(){
        cout<<"op int was called!\n";
        return (int)data;
    }
    char& operator [](int _pos){
        return s[_pos];
    }
    void setData(double input){
        data=input;
    }
    void setString(const char* input){
        s=new char[strlen(input)];
        strcpy(s,input);
    }
};
double f(double a,double b){
    return a-b;
}

void printINT(F& input){
    int out=input;
    printf("%d\n",out);
}
int main(){
    F f;
    f.setData(1.2);
    f.setString("Hello");
    cout<<f[1]<<endl;
    //std::cout<<f(2,1);
    printINT(f);
}