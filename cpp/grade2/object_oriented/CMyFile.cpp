#include <iostream>
#include <cstring>
using namespace std;

class CMyFile
{
private:
    FILE *p;//文件指针
    char path[100];//文件路径名
public:
    CMyFile();//空构造函数
    ~CMyFile();//析构函数
    CMyFile(char[]);//构造函数
    bool OpenFile();// 打开文件，默认方式：打开可“读写”的文件；
    bool CloseFile();//关闭文件
    char GetChar(); //从文件中读取一个字符；
    bool AppendChar(char);//向文件末尾写入一个字符；
    char* GetString(int);//从文件中读入指定长度的字符串；
    bool AppendString(char*);//向文件末尾写入字符串；
    int GetFileSize();//获取文件大小。
};
CMyFile::CMyFile(){printf("please enter path of the file\n");}
CMyFile::~CMyFile(){if(!p)fclose(p);delete p;}
CMyFile::CMyFile(char srcPath[]){p= nullptr;strcpy(path,srcPath);}
bool CMyFile::OpenFile()
{
    p=fopen(path,"a+");//用可读写的方式打开文件
    if(p== nullptr)return false;
    return true;
}
bool CMyFile::CloseFile()//封装fclose函数并给出提示
{
    if(fclose(p))
    {
        printf("close error!\n");
        return false;
    }
    return true;
}
char CMyFile::GetChar()//封装fgetc函数
{
    return fgetc(p);
}
bool CMyFile::AppendChar(char _input)//寻址到文件末尾再添加字符
{
    fseek(p,0L,SEEK_END);
    fprintf(p,"%c",_input);
    rewind(p);
    return true;
}
char * CMyFile::GetString(int length=10)//在当前文件指针之后读取指定长度的字符串，缺省长度为10
{
    if(length>100)
    {
        printf("out of max_length!\n");
        return nullptr;
    }
    char *output = new char[100];
    int i;
    for(i=0;i<length;i++)
    {
        fscanf(p,"%c",&output[i]);
    }
    output[i]=0;
    return output;
}
bool CMyFile::AppendString(char *input=nullptr)//在末尾添加字符串
{
    fseek(p,0L,SEEK_END);
    fprintf(p,"%s",input);
    rewind(p);
    return true;
}
int CMyFile::GetFileSize()//利用ftell来统计字节数
{
    if(!p) return -1;
    rewind(p);
    fseek(p,0L,SEEK_END);
    return ftell(p);
}

int main()
{
    char filename[100];
    cin>>filename;
    CMyFile file1(filename);
    file1.OpenFile();
    file1.AppendChar('A');
    cout<<"getchar:  "<<(char)file1.GetChar()<<endl;
    file1.AppendString("hello,world");
    cout<<"getstring:  "<<file1.GetString(13)<<endl;
    cout<<file1.GetFileSize()<<endl;
    file1.CloseFile();
    return 0;
}