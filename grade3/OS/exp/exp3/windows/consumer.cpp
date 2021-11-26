#include <iostream>
#include <windows.h>
#include "PublicInfo.h"
using namespace std;
int main(int argc, char **argv){
    /*打开信号量*/
    HANDLE MUTEX = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, "osexp3_mutex");
	HANDLE EMPTY = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, "osexp3_empty");
	HANDLE FULL = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, "osexp3_full");

    /*打开共享内存区*/
    //若无同名共享内存区，则创建
	HANDLE hmap = OpenFileMapping(
		FILE_MAP_ALL_ACCESS, 
		FALSE, 
		"osexp3_filemapping"
    );

    /*将共享内存区加载到当前的地址空间*/
    //若成功，返回共享内存空间的首地址指针
	LPVOID pFile = MapViewOfFile(
		hmap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0
    );
	struct ring_buffer* pRingBuf = reinterpret_cast<struct ring_buffer*>(pFile);

    /*消费若干次产品*/
    for (int i = 0; i < CON_GET; i++){
        Sleep(get_random(2000,4000));
        p(FULL);
        p(MUTEX);
        int itemValue = pRingBuf->items[pRingBuf->out];
        pRingBuf->items[pRingBuf->out] = 0;
        printTime();
        printf("Consumer(%d) consumed a item that values %d on position %d!\n",
            GetCurrentProcessId(), 
            itemValue,
            pRingBuf->out);
        printBuffer(pRingBuf);
        fflush(stdout);//立马刷新屏幕
        pRingBuf->out = (pRingBuf->out + 1) % BUFFER_SIZE;
        v(EMPTY);
        v(MUTEX);
    }


    //解除映射
    UnmapViewOfFile(pFile);
    CloseHandle(pFile);
    pFile = NULL;

    /*回收信号量*/
    CloseHandle(EMPTY);
	CloseHandle(FULL);
	CloseHandle(MUTEX);
    return 0;
}