/***************************************************************
* File Name: mmap.c
* Author: anda
* mail: anda@qq.com
* Created Time: Sun 05 Apr 2020 06:30:22 PM CST
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/mman.h>
#define NUM 1024*8*8
int main(){
    int i = 0;
    int fd = 0;
    struct timeval tm1,tm2;
    int* idata = (int*)malloc(sizeof(int)*NUM);
    gettimeofday(&tm1, NULL);
    for(i=0;i<NUM;i++){
        idata[i] = i%8000;
    }
    //写入文件
    fd = open("mmapfile.bin",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
//    if(sizeof(int)*NUM != write(fd,(void*)idata,sizeof(int)*NUM)){
//        printf("writing mmapfile failed\n");
//        exit(-1);
//    }
    close(fd);
    // 读取文件
    fd = open("mmapfile.bin",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(sizeof(int)*NUM != read(fd,(void*)idata,sizeof(int)*NUM)){
        printf("reading mmapfile failed\n");
        exit(-1);
    }
    free(idata);
    close(fd);
    gettimeofday(&tm2,NULL);
    printf("time of read/write : %dms\n",tm2.tv_usec - tm1.tv_usec);
    // 使用mmap
    gettimeofday(&tm1, NULL);
    fd = open("mmapfile.bin",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    idata = mmap(NULL,sizeof(int)*NUM,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    for(i=0;i<NUM;i++) idata[i]=1;
    munmap(idata,sizeof(int)*NUM);
    msync(idata,sizeof(int)*NUM,MS_SYNC);
    close(fd);
    gettimeofday(&tm2,NULL);
    printf("time of mmap : %dms\n",tm2.tv_usec - tm1.tv_usec);
    return 0;

    
}
