#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <windows.h>
#include "PublicInfo.h"

//保存子进程句柄
HANDLE handle[PRO_N+CON_N];

//0~PRO_N-1为生产者，PRO_N~PRO_N+CON_N-1为消费者
void CreateProcessByType(int id){
    TCHAR szcmdLine[MAX_PATH];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    bool bCreatedOK = false;
    if(id<PRO_N){
        sprintf(szcmdLine,"%s","producer");
    }else if(id>=PRO_N){
        sprintf(szcmdLine,"%s","consumer");
    }
    bCreatedOK = CreateProcess(
        NULL,
        szcmdLine,
        NULL,
        NULL,
        FALSE,
        CREATE_DEFAULT_ERROR_MODE,
        NULL,
        NULL,
        &si,
        &pi);

    if(bCreatedOK){
        handle[id]=pi.hProcess;//便于后面的WaitForMultipleObjects进程同步
        // CloseHandle(pi.hProcess);
        // CloseHandle(pi.hThread);
    }else{
        perror("createProcessByType");
        exit(1);
    }
}

int main(int argc,char *argv[]){
    printf("start!\n\n");
    /*建立信号量*/
    HANDLE MUTEX = CreateSemaphore(NULL, 1, 1, "osexp3_mutex");
	HANDLE EMPTY = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, "osexp3_empty");
	HANDLE FULL = CreateSemaphore(NULL, 0, BUFFER_SIZE, "osexp3_full");

    /*打开共享内存区*/
    //若无同名共享内存区，则创建
	HANDLE hmap = CreateFileMapping(
		INVALID_HANDLE_VALUE, 
		NULL, 
        PAGE_READWRITE,
        0,
        SHM_SIZE,
		"osexp3_filemapping");
    if(hmap == INVALID_HANDLE_VALUE){
        perror("OpenFileMapping");
        exit(1);
    }
    /*将共享内存区加载到当前的地址空间*/
    //若成功，返回共享内存空间的首地址指针
	LPVOID pFile = MapViewOfFile(
		hmap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0);
    //初始化内存区域
    if(!pFile){
        perror("MapViewOfFile");
        exit(1);
    }
	struct ring_buffer* pRingBuf = reinterpret_cast<struct ring_buffer*>(pFile);
    pRingBuf->in = 0;
    pRingBuf->out = 0;
    memset(pRingBuf, 0, sizeof(struct ring_buffer));
    //解除映射
    UnmapViewOfFile(pFile);
    CloseHandle(pFile);
    pFile = NULL;

    /*创建子进程*/
    for(int i = 0;i<PRO_N+CON_N;i++){
        //0~PRO_N-1为生产者，PRO_N~PRO_N+CON_N-1为消费者
        CreateProcessByType(i);
    }
    
    /*等待子进程关闭*/
    WaitForMultipleObjects(PRO_N+CON_N,handle,true,INFINITE);

    /*回收信号量*/
    CloseHandle(EMPTY);
	CloseHandle(FULL);
	CloseHandle(MUTEX);
    printf("end!");
}