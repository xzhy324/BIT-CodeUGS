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

    /*生产若干次产品*/
    for (int i = 0; i < PRO_GIVE; i++){
        Sleep(get_random(2000,4000));
        p(EMPTY);
        p(MUTEX);
        pRingBuf->items[pRingBuf->in] = get_random(10,100);
        printTime();
        printf("Producer(%d) produced a item that values %d on position %d!\n",
            GetCurrentProcessId(),
            pRingBuf->items[pRingBuf->in],
            pRingBuf->in);
        printBuffer(pRingBuf);
        fflush(stdout);//立马刷新屏幕
        pRingBuf->in = (pRingBuf->in + 1) % BUFFER_SIZE;
        v(MUTEX);
        v(FULL);
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