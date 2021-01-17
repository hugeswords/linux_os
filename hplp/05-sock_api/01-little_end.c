/***************************************************************
* File Name: 01-little_end.cpp
* Author: anda
* mail: anda@qq.com
* Created Time: Sun 17 Jan 2021 11:40:52 AM CST
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
void byteorder(){
    union{
        int ival;
        char sval[4];
    } test;
    test.ival = 0x01020304;
    if(test.sval[0]==1){
        printf("big endian \n");
    }else if(test.sval[0]==4){
        printf("little endian \n");
    }
}
int main(){
    byteorder();
    return 0;
}
