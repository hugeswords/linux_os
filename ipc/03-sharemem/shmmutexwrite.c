/*向共享内存写入数据*/
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
    //共享内存中存储的数据结构
    struct People{
        char name[10];
        int age;
    };
    int shmid;
    sem_t* sem;
    int age = 10;
    int i = 1;
    char buff[BUFFER_SIZE];
    key_t shmkey;
    // fotk 用来生产唯一ID
    shmkey = ftok("shmmutexread.c",0);
    //
    sem = sem_open(sem_name,O_CREAT,0644,1);
    if(sem==SEM_FAILED){
        printf("unable to create semaphore!");
        sem_unlink(sem_name);
        exit(-1);
    }
    //获取一块共享内存区
    shmid = shmget(shmkey,1024,0666|IPC_CREAT);
    if(shmid==-1){
        printf("create shm is fail\n");
    }
    //将共享内存映射到当前进程的地址中，之后直接对进程中addr操作就是对共享内存操作
    struct People* addr;
    addr = (struct People*)shmat(shmid,0,0);
    if(addr==(struct People*)-1)
        printf("shm shmat is fail\n");
    //向共享内存写入数据
    addr->age = 0;
    printf("写进程映射共享内存地址=%p\n",addr);
    do{
        sem_wait(sem);
        memset(buff,0,BUFFER_SIZE);
        memset((addr+i)->name,0,BUFFER_SIZE);
        printf("写进程：输入一些姓名到共享内存:\n");
        if(fgets(buff,BUFFER_SIZE,stdin)==NULL){
            perror("fgets");
            sem_post(sem);
            break;
        }
        strncpy((addr+i)->name,buff,strlen(buff)-1);
        (addr+i)->age==++age;
        addr->age++;
        i++;
        sem_post(sem);
        sleep(1);
    }while(strncmp(buff,"quit",4)!=0);
    //将共享内存与当前程序断开
    if(shmdt(addr)==-1)
        printf("shmdt is fail\n");
    sem_close(sem);
    sem_unlink(sem_name);
    return 0;
}
