# include <iostream>
using namespace std;

template<class T>
class CMyStack{
private:
    unsigned int max_size;//栈的最大大小
    T *stack;//使用泛型
    int stack_top;//栈顶指示器
public:
    explicit CMyStack(unsigned int=100);
    bool empty();//判空
    bool full();//判满
    bool push(const T&);//入栈
    bool pop();//出栈
    void clear();//清空栈
    T peek();//获取栈顶元素
};
template<class T>
CMyStack<T>::CMyStack(unsigned int n)
{
    stack = new T[n];
    max_size = n;
    stack_top = 0;
}
template<class T>
bool CMyStack<T>::empty() {return stack_top==0;}

template<class T>
bool CMyStack<T>::full() {return stack_top==max_size;}

template<class T>
void CMyStack<T>::clear() {stack_top=0;}

template<class T>
bool CMyStack<T>::pop()
{//出栈；
    if (stack_top>0)
    {
        --stack_top;
        return true;
    }
    return false;
}
template<class T>
bool CMyStack<T>::push(const T& input)
{
    if (stack_top<max_size)
    {
        stack[stack_top++] = input;
        return true;
    }else{
        cout<<"the stack is full!\n";
        return false;
    };
}

template<class T>
T CMyStack<T>::peek()
{
    if (stack_top>0)return stack[stack_top-1];
    else return (T)NULL;
}

int main()
{
    int StackSize=2;
    CMyStack<char> Stack1(StackSize);
    Stack1.push('a');
    Stack1.push('b');
    cout<<Stack1.full()<<endl;
    cout<<Stack1.peek()<<endl;
    Stack1.pop();
    cout<<Stack1.peek()<<endl;
    Stack1.clear();
    cout<<Stack1.empty()<<endl;
}