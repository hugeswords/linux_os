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

int main(int argc, char* argv[]){
    if( argc <=2 ){
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd>=0);

    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("connect failed\n");
    }else{
        const char* data = "yeanda";
        const char* data2 = "hello";
        send(sockfd, data, strlen(data), 0);
        send(sockfd, data2, strlen(data2), 0);
        send(sockfd, data, strlen(data), 0);
        
    }
    close(sockfd);
    return 0;

}
