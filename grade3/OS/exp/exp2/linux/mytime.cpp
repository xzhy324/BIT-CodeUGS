#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <wait.h>
#include <stdlib.h>

void printTime(unsigned long us){
    unsigned long hour = us /(unsigned long)3600000000;
    us -= hour*(unsigned long)3600000000;
    unsigned long minute = us/60000000;
    us-= minute*60000000;
    unsigned long second = us/1000000;
    us-=1000000*second;
    unsigned long ms = us/1000;
    us -= ms*1000;
    printf("%ldh %02ldm %02lds %03ldms %03ldus",hour,minute,second,ms,us);
}

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("plz enter the path/file\n");
        exit(-1);
    }
    timeval start;
    timeval end;
    gettimeofday(&start,nullptr);

    pid_t child_process_pid;
    child_process_pid = fork();
    if(child_process_pid==0){
        /*in child process ，负责运行目标程序*/
        char *target_program = argv[1];
        if(argc==2){
            /*未指定目标程序的运行时间*/
            execlp(target_program,target_program,nullptr); //执行argv[1]指向的内容，参数为空
        }else if(argc==3){
            /*指定了特定目标程序的运行时间*/
            execlp(target_program,target_program,argv[2],nullptr);
        }
    }else{
        wait(nullptr);
    }  
    
    gettimeofday(&end,nullptr);
    unsigned long spent_us = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printTime(spent_us);
    return 0;
}