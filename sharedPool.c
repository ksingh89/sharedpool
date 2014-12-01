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
#include "spd.h"
#include "ssp.h"

extern struct sspMessage* readMessage(char*, size_t);
extern struct IP_ADDR ip[CACHEVALUE];
extern int cacheId;

int main(int argc, char **argv)
{
	enum state stId;
	int i, port, pid, listenfd, socketfd, hit, option, id, ret, temp;
	socklen_t length;
	struct sockaddr_in cli_addr;
	struct sockaddr_in serv_addr;
	char buffer[BUFSIZE];
	struct sspMessage *reqMessage;
//	handler thread id and Main thread
	pthread_t hdlTid;

	printf("%s\n",__FUNCTION__);
//	initSharedPool();

//	creating server socket 
	listenfd = socket(AF_INET, SOCK_DGRAM,0);

	//	initializing server socket
	setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &option, 4);
	serv_addr.sin_family = AF_INET;
//	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
//	serv_addr.sin_port = htons(atoi(&argv[1]));
	serv_addr.sin_port = htons(PORT_LISTEN);

	//	Bind the address
	if(bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
	{
		printf("system call bind error\n");
		exit(0);
	}

	for(i=1; ;i++)
	{
		printf("Listening on port %d for DHCP\n", PORT_LISTEN);
		length = sizeof(cli_addr);
		ret = recvfrom(listenfd, buffer, BUFSIZE, 0, (struct sockaddr *)&cli_addr, &length);
		if(ret <= 0 )
		{
			printf("\nNo Data received!! ERROR!!!\n");
			exit(0);
		}
		reqMessage = readMessage(buffer, sizeof(buffer));
		//temp.messageType = reqMessage->messageType;
		//pthread_create(&hdlTid,NULL, (void*)&hdlDHCP, (void*)temp);
		pthread_create(&hdlTid,NULL, (void*)&hdlDHCP, (void*)reqMessage);
		pthread_join(hdlTid, NULL);
//		if(!ip[cacheId].ipState)
//		{
//			if(reqMessage->messageType == DHCPDISCOVER)
//				ip[cacheId].ipState = ASSIGNED;
//			else if(reqMessage->messageType == DHCPREQUEST)
//				ip[cacheId].ipState = INUSE;
//			else
//				printf("ERROR changing IP STATE!!! \n\n");
			printf("cacheId = %d", cacheId);
			printf("\nIP value:%s and State:%d\n", ip[cacheId].ip_addr, ip[cacheId].ipState);
			ret = sendto(listenfd, (void *)ip[cacheId].ip_addr, sizeof ip[0].ip_addr, 0, (struct sockaddr*)&cli_addr, sizeof cli_addr);
//			if(reqMessage->messageType == DHCPDISCOVER)
//				ip[cacheId].ipState = ASSIGNED;
//			else if(ip[cacheId].ipState == DHCPREQUEST)
//				ip[cacheId].ipState = INUSE;
//			else
//				printf("ERROR changing IP STATE!!! \n\n");
//			cacheId++;
//			if(cacheId >= CACHEVALUE)
//			{
//				cacheId = 0;
//			}
//		}
	}

	return 0;
}

int initSharedPool()
{
	int i;
	printf("%s\n",__FUNCTION__);
	i = sizeof(int);
	return 1;
}


