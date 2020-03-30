#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
int wc = 1;
int rc = 1;
void writer(const char* message, int count, FILE* stream);
void reader(FILE* stream);
int main(){
// 0是读，1是写
int fds[2];
pid_t pid;
//管道函数，入参是2个int元素的数组，也就是两个文件描述符
pipe(fds);
pid = fork();
if( pid == 0){
    FILE* stream;
    // 关闭写端
    close (fds[1]);
    // 取文件描述符，并使一个标准的文件IO流与文件描述符结合
    stream  = fdopen(fds[0], "r");
    //这里如果使用while死循环，就造成的僵尸进程
    reader(stream);
    close(fds[0]);
}else{
    FILE* stream;
    //关闭读端
    close(fds[0]);
    stream = fdopen(fds[1], "w");
    writer("hello,writer", 5, stream);
    close(fds[1]);
}
    return 0;
}

void writer(const char* message, int count, FILE* stream){
    for(; count>0; --count){
        printf("写进程第%d次写入:",wc);
        fprintf(stream, "%s:%d\n",message,wc);
        fflush(stream);
        printf("写进程第%d次阻塞.\n",wc);
        wc++;
        sleep(1);
    }
}

void reader(FILE* stream){
    char buffer[1024];
    while(!feof(stream) && !ferror(stream) && fgets(buffer,sizeof(buffer),stream) != NULL){
        printf("读进程第%d次读取:",rc);
        rc++;
        fputs(buffer, stdout);
    }
}
