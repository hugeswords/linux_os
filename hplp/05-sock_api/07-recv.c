/***************************************************************
* File Name: 06-send.c
* Author: anda
* mail: anda@qq.com
* Created Time: Sun 17 Jan 2021 05:23:06 PM CST
*********************************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 1024
int main(int argc, char* argv[]){
    if( argc <=2 ){
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd>=0);

    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret!=-1);

    ret = listen(sockfd, 5);
    assert(ret!=-1);

    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);

    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_len);
    if(connfd<0){
        printf("error is: %d\n",errno);
    }else{
        char buffer[BUF_SIZE];

        memset(buffer, 0 , BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("get %d byte of data '%s'\n", ret, buffer);

        memset(buffer, 0 , BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("get %d byte of data '%s'\n", ret, buffer);

        memset(buffer, 0 , BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("get %d byte of data '%s'\n", ret, buffer);

        close(connfd);
    }
    close(sockfd);
    return 0;

}
