/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* 用迭代器模式操作的字符串类CMyString
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
using namespace std;
//-----------------------------------------------

// 定义自己的字符串类
class CMyString
{
public:
	CMyString(const char* = NULL);
	CMyString(const CMyString&);
	~CMyString();
	int Length();                 // 获取字符串长度
	char& operator[](int index);      // 获取指定位置的字符
	CMyString& operator=(const CMyString&);
	friend ostream& operator<<(ostream&, const CMyString&);

	class Iterator;    // 向前引用，对后续的友元类进行声明
	friend Iterator;

	// 将类iterator定义在类CMyString中，目的是说明该迭代器仅为当前类服务。
	class Iterator
	{
	public:
		Iterator(CMyString& str, bool isEnd = false)
		{
			p = str.m_pString;                 // 指向第一个元素
			if (isEnd)  p += str.m_iSize - 1;  // 指向最后一个元素
		}
		Iterator operator++(int)  // 重载++为后缀运算符
		{
			p++;
			return *this;
		}
		Iterator operator++()    // 重载++为前缀运算符
		{
			Iterator temp(*this);
			p++;
			return temp;
		}
		Iterator operator--(int)  // 重载--为后缀运算符
		{
			p--;
			return *this;
		}
		Iterator operator--()    // 重载--为前缀运算符
		{
			Iterator temp(*this);
			p--;
			return temp;
		}
		bool operator<(const Iterator& it) { return p < it.p + 1; }
		char& operator*() { return *p; }
	private:
		char* p;	           // 当前容器元素的地址
	};  // end of Iterator

	Iterator Begin() { return  Iterator(*this); }     // 重置迭代器指向容器的第一个元素
	Iterator End() { return Iterator(*this, true); }  // 重置迭代器指向容器的最后一个元素

protected:
	char* m_pString;             // 保存字符串
	int m_iSize;                 // 字符串长度
};

// CMyString的构造函数，用于保存指定的字符串
CMyString::CMyString(const char* ch)
{
	if (ch == NULL)
		m_iSize = 0;
	else
	{
		for (m_iSize = 0; ch[m_iSize] != '\0'; m_iSize++);  // 求字符串长度
	}
	m_pString = new char[m_iSize + 1];
	for (int i = 0; i < m_iSize; i++)	m_pString[i] = ch[i];   // 保存字符串
	m_pString[m_iSize] = '\0';
}

/*
*  实现：CMyString的拷贝构造函数，用参数对象my初始化当前对象。
*  参数：my初始化对象时的参数对象
*/
CMyString::CMyString(const CMyString& my)
{
	m_iSize = my.m_iSize;
	m_pString = new char[m_iSize + 1];
	for (int i = 0; i < m_iSize; i++)
		m_pString[i] = my.m_pString[i];
	m_pString[m_iSize] = '\0';
}

// 析构函数，释放程序中动态申请的内存空间。
CMyString::~CMyString()
{
	if (m_pString != NULL)		delete[] m_pString;
}

/*
*  实现：重载下标运算符[ ]，获得指定位置的字符
*  参数：index：指定字符串中的位置
*  返回：指定位置对应的字符
*/
char& CMyString::operator[ ](int index)
{
	if (index < 0 || index >= m_iSize) 	return m_pString[m_iSize];
	else  return m_pString[index];
}

// 获取字符串长度
int CMyString::Length() { return m_iSize; }	
CMyString& CMyString::operator=(const CMyString& my)
{
	// 完成赋值之前，先要删除待赋值对象中的字符串空间
	if (m_iSize != 0)	delete[] m_pString;
	m_iSize = my.m_iSize;
	m_pString = new char[m_iSize + 1];
	for (int i = 0; i < m_iSize; i++)
		m_pString[i] = my.m_pString[i];
	m_pString[m_iSize] = '\0';
	return *this;
}

ostream& operator<<(ostream& os, const CMyString& my)
{
	return os << my.m_pString;
}

int_least32_t main()
{
	CMyString str("CMyString");

	cout << "Use statement \"for\" to print a string." << endl;
	for (int i = 0; i < str.Length(); i++)
		cout << str[i] << ' ';
	cout << endl << endl;

	cout << "Use iterator to print a string." << endl;
	for (CMyString::Iterator it = str.Begin(); it < str.End(); it++)
		cout << *it << ' ';

	cout << endl << endl;
}