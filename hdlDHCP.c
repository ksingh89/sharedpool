#include <stdio.h>

#include "sharedPool.h"
#include "hdlCache.h"
#include "spd.h"
#include "ssp.h"
#include "hdlDHCP.h"

//extern int hdlCache(int, char*);
extern struct IP_ADDR ip[CACHEVALUE];
extern int hdlCache(int);
extern unsigned int cacheId;

void hdlDHCP(void* ptr)
{
	int *event=NULL;
	int x;
	char *ip;
	event = (int*)ptr;
	enum stateHdlDhcp state;
//	initHdlDhcpThread();
	printf("%s\n",__FUNCTION__);
	printf("event %d\n",*event);
	switch(*event)
	{
		case DHCPDISCOVER:
			if(!cacheId)
			{
			x = DHCPDISCOVER;
//			Can modify request for previously assigned IP
			hdlDiscover(x);
			}
			else
			{
//				ip[cacheId].ipState = ASSIGNED;
				hdlDiscover(DHCPDISCOVERFROMCACHE);
			}
			break;
		case DHCPREQUEST:
			x = DHCPREQUEST;
//			Can modify the request for previously assigned IP
			hdlRequest(x);
			break;
		case DHCPDECLINE:
			x = DHCPDECLINE;
			hdlDecline(x);
			break;
	}
//	printf("\nIP ADDR = %s\n",ip);
	pthread_exit(NULL);
}

int initHdlDhcpThread()
{
	printf("%s\n",__FUNCTION__);
	return 1;
}
//int hdlDiscover(int event, char* ip)
int hdlDiscover(int event)
{
	//char *ipdis;
//	ipdis = ip;
	printf("%s\n",__FUNCTION__);
//	transfers the call to the cache thread for processing
//	hdlCache(event, ipdis);
	hdlCache(event);
//	ip = ipdis;
	return 1;
}

int hdlRequest()
{
	int event = 1;
	printf("%s\n",__FUNCTION__);
//	transfers the call to the cache thread for processing
	hdlCache(event);
	return 1;
}

int hdlDecline()
{
	int event = 1;
	printf("%s\n",__FUNCTION__);
//	transfers the call to the cache thread for processing
	//hdlCache(event);
	return 1;
}
