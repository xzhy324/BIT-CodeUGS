#include "iostream"
using namespace std;

class pet{
public:
    virtual ~pet()=0;
};

class dog : public pet{};
class cat : public pet{};

int main(){
    dog *a=new dog;
    dog* b=dynamic_cast<dog*>(a);
}