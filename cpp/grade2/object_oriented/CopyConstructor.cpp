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
    void print()const{
        cout<<x<<" "<<y<<endl;
    }
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
    //在c11之后，匿名对象会申请在系统堆空间，从而减少拷贝构造函数的调用。
    //Point B(g());
    Point B=g();//效果类似上一条语句
    //Point B;B=g();

    B.print();


    int a;
    cin>>a;
    return 0; 
}