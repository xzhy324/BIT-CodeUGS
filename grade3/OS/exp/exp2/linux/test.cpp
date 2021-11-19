#include "iostream"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
    printf("target_program started!\n");
    int sleep_seconds = 3;
    if(argc==2){
        /*指定了程序运行的时间*/
        sleep_seconds = atoi(argv[1]);
        printf("sleep_seconds:%d\n",sleep_seconds);
        sleep(sleep_seconds);
    }else if(argc==1){
        sleep(sleep_seconds);
    }
    printf("target_program ended!\n");
    exit(0);
}