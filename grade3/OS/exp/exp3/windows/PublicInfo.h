/*
 *定义若干使用的常量
 *以及生产者和消费者公用的数据结构以及函数
 *
 */
#include <ctime>
#define BUFFER_SIZE 3
#define PRO_N 2
#define PRO_GIVE 6
#define CON_N 3
#define CON_GET 4
#define SHM_SIZE 1024
#define p(x) WaitForSingleObject(x,INFINITE)
#define v(x) ReleaseSemaphore(x,1,NULL)

//环形缓冲区，注意其中所有元素的访问都要先申请 MUTEX 锁
struct ring_buffer {
    int items[BUFFER_SIZE];  //缓冲区数据
    int in;  //生产指针
    int out;  //消费指针
};

int get_random(int from,int to){
    if(to<from){
        perror("get_random");
        exit(1);
    }
    srand(GetCurrentProcessId() + time(NULL));
    return rand()%(to+1-from)+from;
}

void printTime(){
    time_t t;
    time(&t);
    printf("%s", ctime(&t));
}

void printBuffer(struct ring_buffer *buffer){
    printf("BUFFER:[ ");
    for(int i = 0; i < BUFFER_SIZE;i++){
        printf("%02d ",buffer->items[i]);
    }
    printf("]\n\n");
}