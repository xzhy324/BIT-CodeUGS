#include "iostream"
using namespace std;
class instrument{
public:
    virtual void play()const{
       // cout<<"instrument::play()\n";
    }
};

class wind : public instrument{
public :
    void play()const{
        cout<<"wind::play()\n";
    }
};

void tune(const instrument &p){
    p.play();
}

int main(){
    wind p;
    tune(p);
}