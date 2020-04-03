#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct _msg_buf{
	long type;
	char buf[100];
} msg_buf;
int main(){
	int key;
	int qid;
	msg_buf buf;
	key = ftok(".", 10);
	qid = msgget(key, IPC_CREAT|0666);
	printf("key: %d\nqid: %d\n",key, qid);
	buf.type = 10;
	printf("请输入一些消息，每条消息用回车结束，如果输入quit，程序停止\n");
	while(1){
		fgets(buf.buf, 100, stdin);
		if(strncmp(buf.buf,"quit",4)==0){
			if(msgctl(qid, IPC_RMID, NULL)<0){
				perror("msgctl");
				exit(-1);
			}else{
				printf("successfully remove %d queue/n",qid);
				//删除消息队列成功
				exit(0);
			}
		}
		if(msgsnd(qid,(void*)&buf, 100, 0)<0){
			perror("message");
			exit(-1);
		}
	}
	return 0;
}
