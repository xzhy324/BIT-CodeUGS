#include <iostream>
#include <windows.h>
#include <cstring>
using namespace std;
const DWORD default_wait_milliseconds = 20000; // milliseconds = 20s
void printTime(unsigned long us){
    unsigned long hour = us /(unsigned long)3600000000;
    us -= hour*(unsigned long)3600000000;
    unsigned long minute = us/60000000;
    us-= minute*60000000;
    unsigned long second = us/1000000;
    us-=1000000*second;
    unsigned long ms = us/1000;
    us -= ms*1000;
    printf("%ldh %02ldm %02lds %03ldms",hour,minute,second,ms);
}

int main(int argc, char* argv[])
{
    if(argc == 1){
        printf("plz enter the path/file\n");
        exit(-1);
    }

    long start_time,end_time;
    start_time = GetTickCount();//返回启动到现在的秒数

	STARTUPINFO si = {sizeof(si)};
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;

    char *szCommandLine;
    if(argc==2){
        /*未指定子进程运行时间*/
        szCommandLine = argv[1];
    }else if(argc==3){
        /*指定了特定子进程的运行时间*/
        char *s_tmp = strcat(argv[1], " ");
        szCommandLine = strcat(s_tmp,argv[2]);
    }
	BOOL result = CreateProcess (
		NULL,
		szCommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi
    );
	if(result){
        
        WaitForSingleObject(pi.hProcess,default_wait_milliseconds);
      
        end_time = GetTickCount();
        long spent_us = (end_time - start_time)*1000;
        printTime(spent_us);

        //关闭新进程关联的句柄，以使得程序正常结束
        CloseHandle (pi.hThread);
		CloseHandle (pi.hProcess);

	}else{
        int nError = GetLastError();
		cout<<"fail to create process:"<<nError<<endl;
	}
    return 0;
}