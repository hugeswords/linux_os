#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define FIFO "myfifo"
#define BUFF_SIZE 1023
int main(int argc, char* argv[]){
    char buff[BUFF_SIZE];
    int real_write;
    int fd;
    int rw = 1;
    //测试FIFO是否存在，若不存在，mkfifo一个FIFO
    if(access(FIFO,F_OK)== -1){
        if((mkfifo(FIFO,0666)<0 &&(errno!=EEXIST))){
            printf("can not create fifo file!\n");
            exit(-1);
        }
    }
    // 调用open以只写的方式打开FIFO，返回文件描述符fd
    if((fd=open(FIFO,O_WRONLY))==-1){
        printf("open filo error!\n");
        exit(-1);
    }
    // 调用write将buff写到文件描述符fd指向的FIFO中
    do{
        printf("请输入写入到文件描述符fd指向的FIFO中:\n");
        gets(buff);
        if((real_write=write(fd,buff,BUFF_SIZE))>0)
            printf("第%d次写入管道:'%s'.\n",rw++,buff);
    }while(strlen(buff)!=0);
    close(fd);
    return 0;
}
