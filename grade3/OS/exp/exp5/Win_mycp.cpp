#include<stdio.h>
#include<Windows.h>
#include<string.h>

#define buf_size 4096


//实现将源文件复制到目标路径
void CopyFile(const char * fsource, const char * ftarget)
{
    /*
	查找指定文件路径的文件FindFirstFile()函数
	HANDLE FindFirstFile(LPCTSTR lpFileName, //file name
	LPWIN32_FIND_DATA lpFindFileData	//data buffer
	);
	返回值：如果调用成功，返回值为非0，否则返回值为0.
	*/
    WIN32_FIND_DATA lpfindfiledata;
    HANDLE hfind = FindFirstFile(fsource, &lpfindfiledata);//打开源文件以便于获取源文件的各种信息

    HANDLE hsource = CreateFile(fsource,
                                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
                                OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    HANDLE htarget = CreateFile(reinterpret_cast<LPCSTR>( ftarget),
                                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
                                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    //利用WIN32_FIND_DATA结构体中的文件长度低32位减去文件长度的高32位，得到源文件的大小
    unsigned long size = lpfindfiledata.nFileSizeLow - lpfindfiledata.nFileSizeHigh;
    DWORD wordbit;
    int *BUFFER = new int[size];

    //读取源文件
    ReadFile(hsource,
             BUFFER,
             size,
             &wordbit,
             NULL);

    //写目标文件
    WriteFile(htarget,
              BUFFER,
              size,
              &wordbit,
              NULL);

    //设置各项属性
    SetFileTime(htarget,
                &lpfindfiledata.ftCreationTime,
                &lpfindfiledata.ftLastAccessTime,
                &lpfindfiledata.ftLastWriteTime);

    DWORD dwAttrs = GetFileAttributes(fsource);
    SetFileAttributes(ftarget, dwAttrs);

    CloseHandle(hfind);
    CloseHandle(hsource);
    CloseHandle(htarget);
}

void mycp(const char * fsource, const char * ftarget)
{
    WIN32_FIND_DATA lpfindfiledata;
    char source[buf_size];
    char target[buf_size];
    lstrcpy(source, fsource);
    lstrcpy(target, ftarget);
    lstrcat(source, "\\*.*");//源目录下的所有文件都需要拷贝
    lstrcat(target, "\\");//目标文件夹需要展开
    HANDLE hfind = FindFirstFile(source, &lpfindfiledata);
    while (FindNextFile(hfind, &lpfindfiledata) != 0)
    {
        if ((lpfindfiledata.dwFileAttributes) == 16)//0x10表示目录文件，此时需要级联
        {
            //注意头两个目录文件为 . 和 ..
            if ((strcmp((const char *)lpfindfiledata.cFileName, ".") != 0) && (strcmp((const char *)lpfindfiledata.cFileName, "..") != 0))
            {
                //此时句柄指向源文件夹中的子文件夹
                memset(source, '0', sizeof(source));
                lstrcpy(source,fsource);
                lstrcat(source, "\\");
                lstrcat(source, lpfindfiledata.cFileName);
                lstrcat(target, lpfindfiledata.cFileName);

                CreateDirectory(target,NULL);
                mycp(source, target);

                HANDLE hDir = CreateFile(target, GENERIC_READ|GENERIC_WRITE,
                                         FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

                SetFileTime(hDir,
                            &lpfindfiledata.ftCreationTime,
                            &lpfindfiledata.ftLastAccessTime,
                            &lpfindfiledata.ftLastWriteTime);

                CloseHandle(hDir);
                //将当前工作路径还原，以便于下一个文件/文件夹的正确复制
                lstrcpy(source, fsource);
                lstrcat(source, "\\");
                lstrcpy(target, ftarget);
                lstrcat(target, "\\");
            }
        }
        else//此时句柄指向文件
        {
            memset(source, '0', sizeof(source));
            lstrcpy(source, fsource);
            lstrcat(source, "\\");
            lstrcat(source, lpfindfiledata.cFileName);
            lstrcat(target, lpfindfiledata.cFileName);
            CopyFile(source, target);
            lstrcat(source, "\\");
            lstrcpy(target, ftarget);
            lstrcat(target, "\\");
        }
    }
    CloseHandle(hfind);
}

int main(int argc, char *argv[])
{

    WIN32_FIND_DATA lpfindfiledata;
    if (argc != 3)//输入文件的个数
    {
        printf("Please enter valid parameters !\n");
        printf("For example: mycp sourceDir destinationDir\n");
    }
    else
    {
        if (FindFirstFile(argv[1], &lpfindfiledata) == INVALID_HANDLE_VALUE)//源路径为空
        {
            printf("Can not find the source directory\n");
        }
        else
        {
            if (FindFirstFile(argv[2], &lpfindfiledata) != INVALID_HANDLE_VALUE)//目标路径不为空
            {
                printf("The target directory is already exists\n");
            }
            else if (FindFirstFile(argv[2], &lpfindfiledata) == INVALID_HANDLE_VALUE)
            {
                printf("Create new directory %s\n",argv[2]);

                CreateDirectory(argv[2],NULL);//为目标文件创建目录
                mycp(argv[1], argv[2]);//执行级联的复制

                //打开目标文件句柄，并修改目标文件的时间戳信息
                HANDLE hDir = CreateFile(argv[2],
                                         GENERIC_READ|GENERIC_WRITE,
                                         FILE_SHARE_READ,
                                         NULL,
                                         OPEN_EXISTING,
                                         FILE_FLAG_BACKUP_SEMANTICS,
                                         NULL);
                SetFileTime(hDir,
                            &lpfindfiledata.ftCreationTime,
                            &lpfindfiledata.ftLastAccessTime,
                            &lpfindfiledata.ftLastWriteTime);
                printf("Copy is done !\n");
            }
        }
    }
    return 0;
}
