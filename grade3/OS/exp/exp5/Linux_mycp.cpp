#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <utime.h>
#include <sys/time.h>

#define buf_size 4096


//实现文件到文件的复制，给出两个路径作为参数
void CopyFile(char *fsource, char *ftarget)
{
	int fd = open(fsource, 0);
	int fdr;
	char buf[buf_size];
	struct stat statbuf, statebuf1;
	struct utimbuf timeby;//保存时间戳信息的结构体
	lstat(fsource, &statebuf1);//将源文件统计信息保存到statbuf1
	if (S_ISLNK(statebuf1.st_mode))//对于软链接特殊处理
	{
		int rslt = readlink(fsource, buf, 511);//返回读取到的路径文字数，将路径存入buf
		if(buf[0]=='.'){//访问中出现了相对路径,使用realpath()转化为绝对路径
			char abs_path[buf_size];
			realpath(buf, abs_path);
			strcpy(buf,abs_path);
			rslt = strlen(buf);
		}
		buf[rslt] = '\0';
		symlink(buf, ftarget);	//目标文件软链接到原来的软连接所指向的文件
		//修改新的软链接的时间信息
		struct timeval times[2];
		times[0].tv_sec = statebuf1.st_atime;
		times[0].tv_usec = 0;
		times[1].tv_sec = statebuf1.st_mtime;
		times[1].tv_usec = 0;
		lutimes(ftarget, times);	
		
		return;

	}
	//其余文件复制
	char BUFFER[buf_size];
	int wordbit;
	stat(fsource, &statbuf);
	fdr = creat(ftarget, statbuf.st_mode);
	while ((wordbit = read(fd, BUFFER, buf_size)) > 0)
	{
		write(fdr, BUFFER, wordbit);
	}
	
	timeby.actime = statbuf.st_atime;
	timeby.modtime = statbuf.st_mtime;
	utime(ftarget, &timeby);

	close(fd); 
	close(fdr);
}
//实现级联复制目录
void mycp(const char *fsource, const char *ftarget)
{
	char source[buf_size];
	char target[buf_size];
	char buf[buf_size];
	struct stat statbuf;
	struct utimbuf timeby;
	DIR *dir;
	struct dirent * entry;//获取目录内容所使用的结构体

	strcpy(source, fsource);
	strcpy(target, ftarget);

	dir = opendir(source);//打开目录并返回dir指针
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == 4)//0x4表示的是目录结构
		{
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)//注意目录文件包含.和 ..，应该忽略
			{
				//制作子目录的路径名，以供mycp递归调用
				strcat(source, "/");
				strcat(source, entry->d_name);
				strcat(target, "/");
				strcat(target, entry->d_name);
				//递归复制
				mkdir(target, statbuf.st_mode);//以源文件夹的st——mode创建目标文件夹
				mycp(source, target);
				//读取源文件夹时间信息，并修改目标文件夹时间信息
				stat(source, &statbuf);
				timeby.actime = statbuf.st_atime;
				timeby.modtime = statbuf.st_mtime;
				utime(target, &timeby)
				//还原路径，便于下一个文件/文件夹复制
				strcpy(source, fsource);
				strcpy(target, ftarget);
			}
		}
		else//此时entry指向文件
		{
			//制作源文件的路径名和目标文件的路径名，供CopyFile函数使用
			strcat(source, "/");
			strcat(source, entry->d_name);
			strcat(target, "/");
			strcat(target, entry->d_name);
			//执行文件复制
			CopyFile(source, target);
			//还原路径，便于下一个文件/文件夹复制
			strcpy(source, fsource);
			strcpy(target, ftarget);
		}
	}
}

int main(int argc, char *argv[])
{
	struct stat statbuf;     
	struct utimbuf timeby;  
	DIR * dir;             
	if (argc != 3)          
	{
		printf("Please enter valid parameters !\n");
        printf("For example: mycp sourceDir destinationDir\n");
	}
	else
	{
		if ((dir = opendir(argv[1])) == NULL)//源路径为空
		{
			printf("Can not find the source directory\n");
		}
		else
		{
			if ((dir = opendir(argv[2])) != NULL)//目标路径不为空
			{
				printf("The target directory is already exists\n"); 
			}
			else if ((dir = opendir(argv[2])) == NULL)//正确情况
			{
				stat(argv[1], &statbuf);//保存源目录的统计信息
				timeby.actime = statbuf.st_atime;	
				timeby.modtime = statbuf.st_mtime;
				mkdir(argv[2], statbuf.st_mode);//创建目标目录（使用源目录的st_mode）
				printf("Create new directory %s\n",argv[2]);
				mycp(argv[1], argv[2]);
				utime(argv[2], &timeby);//修改目标目录时间戳
				printf("Copy is done !\n");
			}
		}
	}
	return 0;
}



