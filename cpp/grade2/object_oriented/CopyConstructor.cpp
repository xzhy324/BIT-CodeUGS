#include <iostream>
using namespace std;
class Point{
private:
    int x,y;
public:
    Point(int xx=0,int yy=0){
        x=xx;y=yy;
        cout<<"Objected Constructed!\n";
    }
    Point(const Point &);
    ~Point(){cout<<"Obj destructed!\n";}
};
Point::Point(const Point& p){
    x=p.x;y=p.y;
    cout<<"Copy Constructor was called!\n";
}
Point g(){
    Point A(1,2);
    return A;
}
int main(){

    //Point B(g());
    Point B=(g());//效果类似上一条语句
    //Point B;B=g();
    int a;
    cin>>a;
    return 0; 
}