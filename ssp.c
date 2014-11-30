#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "ssp.h"


int sspDiscover()
{
	printf("%s\n",__FUNCTION__);
	return 1;
}

struct sspMessage* readMessage(char *buffer, size_t size)
{
	struct sspMessage* msg = NULL;
	printf("%s\n",__FUNCTION__);
	if(NULL == buffer)
	{
		printf("\n***BUFFER for readMessage is NULL***");
		return NULL;
	}
	msg = (struct sspMessage*)malloc(sizeof(struct sspMessage));
	memset(msg, 0, sizeof(struct sspMessage));
	memcpy(&(msg->messageType), buffer, 1);
	if(msg->messageType == DHCPDISCOVER)
		msg->event = IPALLOCATION;
	else if(msg->messageType == DHCPREQUEST)
		msg->event = IPCOMMIT;
	else if(msg->messageType == DHCPDECLINE)
			msg->event = IPDECLINE;
	else if(msg->messageType == DHCPRELEASE)
				msg->event = IPDEALLOCATION;
	else
	{
		printf("\nERROR!!");
		return NULL;
	}
	return msg;
}
