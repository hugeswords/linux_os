/***************************************************************
* File Name: rwbfile.c
* Author: anda
* mail: anda@qq.com
* Created Time: Sat 04 Apr 2020 03:28:47 PM CST
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define NUM 10
#define file1 "file1.bin"
#define file2 "file2.bin"
#define OFFSET 0
int main(){
    FILE* sf;
    FILE* df;
    int rnum = 0;
    int data[NUM];
    int digit = 0;
    int i=0,j=10;
    //创建源文件
    sf = fopen(file1,"wb+");
    if(sf<0){
        printf("open file1 error!\n");
        exit(-1);
    }
    //向源文件中写数据
    for(;j>0;j--){
        for(i=0;i<NUM;i++) data[i]=digit;
        digit++;
        rnum = fwrite(data, sizeof(int), NUM, sf);
    }
    //创建目的文件
    df = fopen(file2, "wb+");
    if(df<0){
        printf("open file error!\n");
        exit(1);
    }
    fseek(sf,OFFSET,SEEK_SET);
    printf("file1:\n");
    while((rnum=fread(data,sizeof(int),NUM,sf))>0){
        for(i=0;i<rnum;i++) printf("%d ",data[i]);
        printf("\n");
        fwrite(data,sizeof(int),rnum,df);
    }
    fseek(df,OFFSET,SEEK_SET);
    printf("file2:\n");
    while((rnum=fread(data,sizeof(int),NUM,df))>0){
        for(i=0;i<rnum;i++) printf("%d ",data[i]);
        printf("\n");
    }
    fclose(sf);
    fclose(df);
    return 0;
}
