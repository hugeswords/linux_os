/**/
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 10
#define sem_name "mysem"
int main(){
int shmid;
sem_t* sem;
int i = 1;
key_t shmkey;
// 获取唯一ID
shmkey = ftok("shmmutexread.c",0);
struct People{
    char name[10];
    int age;
};
// 读取共享内存和信号量的IPC
    sem = sem_open(sem_name,0,0644,0);
    if(sem==SEM_FAILED){
        printf("unable to open semaphore");
        sem_close(sem);
        exit(-1);
    }
// 获取共享内存
    shmid  = shmget(shmkey,0,0666);
    if(shmid==-1){
        printf("create shm is failed\n");
        exit(-1);
    }
// 将共享内存映射到当前的进程地址中，之后直接操作addr，就是对共享内存进行操作
    struct People *addr;
    addr = (struct People*)shmat(shmid,0,0);
    if(addr == (struct People*)-1){
        printf("shm shmat is failed\n");
        exit(-1);
    }
    printf("读进程映射的共享内存地址=%p\n",addr);
    /*从共享内存区读取数据*/
    do{
        sem_wait(sem);
        if(addr->age>0){
            printf("\n读进程:绑定到共享内存:%p:姓名%d %s, 年龄%d \n",
            addr, i, (addr+i)->name, (addr+i)->age);
        addr->age--;
        if(strncmp((addr+i)->name, "quit", 4) == 0) break;
        i++;
        }
        sem_post(sem);
    }while(1);
    sem_close(sem);
    /*将共享内存与当前进程断开*/
    if(shmdt(addr)==-1) 
        printf("shmdt is fail\n");
    //彻底清除共享内存
    if(shmctl(shmid,IPC_RMID,NULL)==-1)
        printf("shmctl delete error");
    return 0;
     return 0;
}
