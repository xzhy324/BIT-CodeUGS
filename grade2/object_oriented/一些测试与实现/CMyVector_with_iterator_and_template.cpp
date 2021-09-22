#include <iostream>
using namespace std;
//-----------------------------------------------
// 定义“向量”模板类（线性结构）及其迭代器
template <class T>
class CMyVector
{
public:
	CMyVector();
	~CMyVector();
	void push_back(const T&);

	class iterator;    // 向前引用，对后续的友元类进行声明
	friend iterator;

	// 将类iterator定义在类CMyVector中，目的是说明该迭代器仅为当前类服务。
	class iterator
	{
	public:
		iterator(const CMyVector<T>& V, bool isEnd = false) : vector(V)
		{
			p = vector.storage;                // 指向第一个元素
			if (isEnd)  p += vector.next - 1;  // 指向最后一个元素
		}
		iterator operator++(int)  // 重载++为后缀运算符
		{
			// stash.storage + stash.next是CMyVector<T>的最后一个元素的地址
			p++;

			return *this;
		}
		iterator operator--(int)  // 重载--为后缀运算符
		{
			// stash.storage 是CMyVector<T>的第一个元素的地址
			p--;
			return *this;
		}
		iterator operator++()    // 重载++为前缀运算符
		{
			iterator temp(*this);
			// stash.storage + stash.next是CMyVector<T>的最后一个元素的地址
			p++;
			return temp;
		}
		iterator operator--()    // 重载--为前缀运算符
		{
			iterator temp(*this);
			// stash.storage是CMyVector<T>的第一个元素的地址
			p--;
			return temp;
		}
		bool operator<(const iterator& it) { return p < it.p + 1; }
		bool operator>(const iterator& it) { return p > it.p - 1; }
		T& operator*() { return *p; }		
	private:
		T* p;	           // 当前容器元素的地址
		const CMyVector<T>& vector;
	};
	iterator Begin() { return  iterator(*this); }        // 重置迭代器指向容器的第一个元素
	iterator End() { return  iterator(*this, true); }  // 重置迭代器指向容器的最后一个元素
private:
	int next;               // 保存下一个元素的位置
	T* storage; // 动态分配的数组
};
template<class T>
CMyVector<T>::CMyVector()      // 在初始化列表处初始化常成员变量
{
	storage = new T[100];
	next = 0;
}
template<class T>
CMyVector<T>::~CMyVector() { if (storage != NULL)	 delete[] storage; }
/*
* 功能：增加一个元素到Vector的尾部
* 参数：element：增加一个元素
*/
template<class T>
void CMyVector<T>::push_back(const T& element)
{
	storage[next] = element;
	next++;
}
//-----------------------------------------------
int main()
{
	// Handle int type
	CMyVector<int> intVector;
	for (int i = 0; i < 5; i++) { intVector.push_back(i); }

	for (CMyVector<int>::iterator it = intVector.End(); it > intVector.Begin(); it--)
	{
		cout << *it << endl;
	}
	cout << endl;


	// Handle char type
	CMyVector<char> charVector;
	for (int i = 65; i < 70; i++) { charVector.push_back(i); }

	for (CMyVector<char>::iterator it = charVector.End(); it > charVector.Begin(); it--)
	{
		cout << *it << endl;
	}
	cout << endl;
}