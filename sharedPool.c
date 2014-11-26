#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "sharedPool.h"
#include "hdlDHCP.h"
#include "hdlCache.h"

extern int hdlDHCP(void);
extern int hdlCache(void);

int main(int argc, char *argv)
{
	enum state stId;
	int i, port, pid, listenfd, socketfd, hit, option, id;
	socklen_t length;
	struct sockaddr_in cli_addr; /* static = initialised to zeros */
	struct sockaddr_in serv_addr; /* static = initialised to zeros */

//	handler thread id and cache thread id and main thread id
	pthread_t hdlTid, cacheTid, threads[100];
	printf("Inside Shared Pool main");
//	create threads to segregate work items
//	creating handler thread
	pthread_create(&hdlTid,NULL, (void*)&hdlDHCP, NULL);
//	creating cache thread
	pthread_create(&cacheTid, NULL, (void*)&hdlCache, NULL);
//	initSharedPool();

	(void)setpgrp();                /* break away from process group */
	listenfd = socket(AF_INET, SOCK_DGRAM,0);
	setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &option, 4);
	if(port < 0 || port >60000)
	printf("Invalid port number (try 1->60000)");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
//	Bind the address
	if(bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)
	{
		printf("system call bind error\n");
		exit(0);
	}

	for(i=1; ;i++) {
		length = sizeof(cli_addr);
		if((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0)
		{
			printf("system call accept error");
			exit(0);
		}



		//pthread_attr t_attr;
		//(void) pthread_attr_init(&t_attr);
		//(void) pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);
		//if (pthread_create(&threads[i], NULL, (void * (*)(void *))handle_request, (void *)socketfd) < 0)
			printf("Error creating thread");
		//printf("Thread created:%d\n",threads[i]);
		//                      handle_request(socketfd);
		sleep(1);
	}

//	while(1)
//	{
//		switch(id)
//		{
//			case 1:
//				break;
//			case 2:
//				break;
//			default:
//				break;
//		}
//	}
	return 0;
}

int initSharedPool()
{

}
