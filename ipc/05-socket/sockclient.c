/***************************************************************
* File Name: sockserver.c
* Author: anda
* mail: anda@qq.com
* Created Time: Sat 04 Apr 2020 08:27:42 AM CST
*********************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    int sockfd = -1;
    int len = 0;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //使用网络套接字
    address.sin_family = AF_INET;
    //服务器地址
    address.sin_addr.s_addr  = inet_addr("127.0.0.1");
    address.sin_port = htons(9536);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr*)&address, len);
    if(result == -1){
        perror("message");
        exit(-1);
    }
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);

}

