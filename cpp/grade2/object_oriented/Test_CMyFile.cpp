// ͬѧ�ǿ����������main��������һ����д��CMyFile�࣬��س�Ա�������Ը�Ϊ�㶨��Ľӿڡ�
// �����������ļ������Ƿ���ȷ��
#include <iostream>
#include <cstring>
using namespace std;

class CMyFile
{
private:
    FILE *p;//�ļ�ָ��
    char path[100];//�ļ�·����
public:
    CMyFile();//�չ��캯��
    ~CMyFile();//��������
    CMyFile(char[]);//���캯��
    bool OpenFile();// ���ļ���Ĭ�Ϸ�ʽ���򿪿ɡ���д�����ļ���
	bool OpenFile(const char[]);
    bool CloseFile();//�ر��ļ�
    char GetChar(); //���ļ��ж�ȡһ���ַ���
    bool AppendChar(char);//���ļ�ĩβд��һ���ַ���
    char* GetString(int);//���ļ��ж���ָ�����ȵ��ַ�����
    bool AppendString(char*);//���ļ�ĩβд���ַ�����
    int GetFileSize();//��ȡ�ļ���С��
};
CMyFile::CMyFile(){printf("please enter path of the file\n");}
CMyFile::~CMyFile(){if(!p)fclose(p);delete p;}
CMyFile::CMyFile(char srcPath[]){p= nullptr;strcpy(path,srcPath);OpenFile();}
bool CMyFile::OpenFile()
{
    p=fopen(path,"a+");//�ÿɶ�д�ķ�ʽ���ļ�
    if(p== nullptr)return false;
    return true;
}
bool CMyFile::OpenFile(const char srcPath[])
{
    p=fopen(srcPath,"a+");//�ÿɶ�д�ķ�ʽ���ļ�
    if(p== nullptr)return false;
    return true;
}
bool CMyFile::CloseFile()//��װfclose������������ʾ
{
    if(fclose(p))
    {
        printf("close error!\n");
        return false;
    }
    return true;
}
char CMyFile::GetChar()//��װfgetc����
{
    return fgetc(p);
}
bool CMyFile::AppendChar(char _input)//Ѱַ���ļ�ĩβ������ַ�
{
    fseek(p,0L,SEEK_END);
    fprintf(p,"%c",_input);
    rewind(p);
    return true;
}
char * CMyFile::GetString(int length=10)//�ڵ�ǰ�ļ�ָ��֮���ȡָ�����ȵ��ַ�����ȱʡ����Ϊ10
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
	rewind(p);
    return output;
}
bool CMyFile::AppendString(char *input=nullptr)//��ĩβ����ַ���
{
    fseek(p,0L,SEEK_END);
    fprintf(p,"%s",input);
    rewind(p);
    return true;
}
int CMyFile::GetFileSize()//����ftell��ͳ���ֽ���
{
    if(!p) return -1;
    rewind(p);
    fseek(p,0L,SEEK_END);
    return ftell(p);
}

int main()
{
	CMyFile myFile;
	bool right = myFile.OpenFile("TestFile.txt");   // ע���ļ�·��
	if (right == NULL) return 0;

	char str[20];
	myFile.AppendString("hello");  // ���ļ���β����д��һ���ַ����������Ա�����ӿڿ����޸�Ϊ����д��ĺ����ӿ�
	cout<<myFile.GetString(3)<<endl;   // ���ļ��ж���һ������Ϊ3���ַ����������Ա�����ӿڿ����޸�Ϊ����д��ĺ����ӿ�


	// ��һ�����һ���ַ��ķ�ʽ����������ı��ļ���
	// ע�⣺����������Ƿ���ȷ��
	int ch = myFile.GetChar();
	while (ch != -1)
	{
		if (ch == 10)  // 10�����з���ASCII
			cout << (char)ch;
		else
			cout << (char)ch;

		ch = myFile.GetChar();
	}

	cout << endl << endl << "The size of file is " << myFile.GetFileSize() << " characters." << endl;

	// myFile.Close();  // ʵ�������������Բ�д�����Ҫ�ر��ļ���������Զ��رա�
}