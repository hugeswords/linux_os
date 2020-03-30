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
    int real_read;
    int fd;
    int rc = 1;
    if(access(FIFO, F_OK)==-1){
        if((mkfifo(FIFO,0666)<0)&&(errno!=EEXIST)){
            printf("can not create fifo file!\n");
            exit(-1);
        }
    }
    if((fd=open(FIFO,O_RDONLY))==-1){
        printf("open fifo error!\n");
        exit(-1);
    }
    while(1){
        memset(buff,0,BUFF_SIZE);
        if((real_read=read(fd,buff,BUFF_SIZE))>0){
            printf("第%d次读取管道:'%s'.\n",rc++,buff);
        }
        else break;
    }
    close(fd);
    return 0;
}
