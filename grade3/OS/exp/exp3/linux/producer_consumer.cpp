#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>

#define BUFFER_SIZE 3
#define PRO_N 2
#define PRO_GIVE 6
#define CON_N 3
#define CON_GET 4
#define SHM_SIZE 1024

#define SHM_KEY 130
#define SEM_KEY 301

//信号量定义
#define FULL 0
#define EMPTY 1
#define MUTEX 2

//环形缓冲区，注意其中所有元素的访问都要先申请 MUTEX 锁
struct ring_buffer {
    int items[BUFFER_SIZE];  //缓冲区数据
    int in;  //生产指针
    int out;  //消费指针
};

int sem_set_id;
int shm_id;
struct ring_buffer* shmptr;

//generate a random num in [from,to]
int get_random(int from,int to){
    if(to<from){
        perror("get_random");
        exit(1);
    }
    srand(getpid() + time(NULL));
    return rand()%(to+1-from)+from;
}

//打印当前时间
void printTime(){
    time_t t;
    time(&t);
    printf("%s", ctime(&t));
}

//打印缓冲区内容
void printBuffer(){
    printf("BUFFER:[ ");
    for(int i=0;i<BUFFER_SIZE;i++){
        printf("%02d ",shmptr->items[i]);
    }
    printf("]\n\n");
}

void p(int sem_num){
    struct sembuf op;
    op.sem_num = sem_num;  //信号量集合中元素的索引
    op.sem_op = -1;  //每次减一
    op.sem_flg = 0;
    semop(sem_set_id,&op,1);  //最后一个参数表示一次需进行操作的数组sem_buf中的元素数
}

void v(int sem_num){
    struct sembuf op;
    op.sem_num = sem_num;  //信号量集合中元素的索引
    op.sem_op = 1;  //每次增一
    op.sem_flg = 0;
    semop(sem_set_id,&op,1);  //最后一个参数表示一次需进行操作的数组sem_buf中的元素数
}

//设置三个信号量empty，full，mutex
void set_semSet(int flag ,int val){//flag is the name of semphonere , val is the default value
    int semctl_result = semctl(sem_set_id,flag,SETVAL,val);
    if(semctl_result==-1){
        perror("semctl error");
        exit(1);
    }
}
int main(int argc,char *argv[]){
    printf("start!\n\n");

    //根据SHMKEY获取一段共享内存
    shm_id = shmget(SHM_KEY,SHM_SIZE,IPC_CREAT | 0666);
    
    if(shm_id==-1){
        perror("shmget error");
        exit(1);
    }
    //设置共享缓冲区的0初值
    shmptr = (struct ring_buffer *)shmat(shm_id,0,0);
    memset(shmptr,0,sizeof(struct ring_buffer));
    shmdt(shmptr);  //断开与共享区的连接


    //根据SEM_KEY获取一个信号量集合
    //该集合有3个信号量，EMPTY,FULL,MUTEX
    sem_set_id = semget(SEM_KEY,3,IPC_CREAT|0666);  
    if(sem_set_id==-1){
        perror("semget error");
        exit(1);
    }

    //设置三个信号量的初值
    set_semSet(EMPTY,BUFFER_SIZE);
    set_semSet(FULL,0);
    set_semSet(MUTEX,1);
    

    //生产者
    for(int j=0;j<PRO_N;j++){
        int child_pid = fork();
        switch(child_pid){
            case -1:
                perror("fork error!");
                exit(1);
            case 0://生产者子进程
                for(int i=0;i<PRO_GIVE;i++){
                    sleep(get_random(1,3));
                    p(EMPTY);
                    p(MUTEX);
                    shmptr = (struct ring_buffer *)shmat(shm_id,0,0);
                    //in指针总是指向空位
                    shmptr->items[shmptr->in] = get_random(10,100);
                    printTime();
                    printf("Producer(%d) produced a item that values %d on position %d!\n",
                        getpid(),
                        shmptr->items[shmptr->in],
                        shmptr->in);
                    printBuffer();
                    fflush(stdout);//立马刷新屏幕
                    shmptr->in = (shmptr->in + 1) % BUFFER_SIZE;
                    shmdt(shmptr);
                    v(FULL);
                    v(MUTEX);
                }
                exit(0);
            default:break;//父进程继续
        }
    }

    //消费者
    for(int j=0;j<CON_N;j++){
        int child_pid =fork();
        switch(child_pid){
            case -1:
                perror("fork error!");
                exit(1);
            case 0://子进程
                for(int i=0;i<CON_GET;i++){
                    sleep(get_random(2,4));
                    p(FULL);
                    p(MUTEX);
                    shmptr = (struct ring_buffer *)shmat(shm_id,0,0);
                    //out指针总是指向满位
                    int itemValue = shmptr->items[shmptr->out];
                    shmptr->items[shmptr->out] = 0;
                    printTime();
                    printf("Consumer(%d) consumed a item that values %d on position %d!\n",
                        getpid(),
                        itemValue,
                        shmptr->out);
                    printBuffer();
                    fflush(stdout);//立马刷新屏幕
                    shmptr->out = (shmptr->out + 1) % BUFFER_SIZE;
                    shmdt(shmptr);
                    v(EMPTY);
                    v(MUTEX);
                }
                exit(0);
            default:break;//父进程继续
        }
    }
    //等待所有子进程退出
    while(wait(0) != -1);
    //删除两个IPC变量
    semctl(sem_set_id, IPC_RMID,0);
    shmctl(shm_id, IPC_RMID,0);
    fflush(stdout);
    printf("end!");
}