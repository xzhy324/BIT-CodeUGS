#include "iostream"
using namespace std;
class F{
public:
    double operator () (double a, double b){
        return a+b;
    }
};
double f(double a,double b){
    return a-b;
}
int main(){
    F f;
    std::cout<<f(2,1);

}