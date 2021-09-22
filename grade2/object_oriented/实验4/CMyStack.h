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
    int size();
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
int CMyStack<T>::size()
{//出栈；
    return stack_top;
}
template<class T>
bool CMyStack<T>::push(const T& input)
{
    if (stack_top<max_size)
    {
        stack[stack_top++] = input;
        return true;
    }else{
        return false;
    };
}

template<class T>
T CMyStack<T>::peek()
{
    if (stack_top>0)return stack[stack_top-1];
    return (T)NULL;
}