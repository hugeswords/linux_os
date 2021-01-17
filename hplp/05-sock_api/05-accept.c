/***************************************************************
* File Name: 03-backlog.c
* Author: anda
* mail: anda@qq.com
* Created Time: Sun 17 Jan 2021 04:44:19 PM CST
*********************************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h> // errno 似乎是一个全局变量
static int stop = 0;
// sigterm信号处理函数，触发时结束主程序中的循环
static void handle_term(int sig){
    stop = 1;
}
int main(int argc, char* argv[]){
    signal(SIGTERM, handle_term);
    if (argc <= 3){
        printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
        // usage ./a.out 127.0.0.1 9999 20
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    //创建一个ipv4 socket地址
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(sock, backlog);
    assert(ret != -1);

    while(!stop){
        sleep(1);
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int connfd = accept(sock, (struct sockaddr*)&client, &client_len);
        if(connfd < 0){
            printf("error is %d\n", errno);
        }else{
            char remote[INET_ADDRSTRLEN];
            printf("connect with ip: %s and port: %d\n",
                inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN),
                ntohs(client.sin_port));
            close(connfd);
        }
    }

    close(sock);
    return 0;

}

