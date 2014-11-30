#include <stdio.h>
#include <time.h>
#include "sharedPool.h"
#include "hdlCache.h"
#include "spd.h"
#include "ssp.h"
#include "hdlDHCP.h"

//extern int hdlCache(int, char*);
extern struct IP_ADDR ip[CACHEVALUE];
extern int hdlCache(int);
extern int getIpFromCache();
extern int cacheId;

void hdlDHCP(void* ptr)
{
	int *event=NULL;
	int x;
	char *ip1;
	event = (int*)ptr;
	enum stateHdlDhcp state;
//	initHdlDhcpThread();
	printf("%s\n",__FUNCTION__);
	printf("event = %d",*event);
	switch(*event)
	{
		case DHCPDISCOVER:
			printf("\nIn DHCPDISCOVER..");
			hdlDiscover(DHCPDISCOVER);
//			else
//			{
//				//ip[cacheId].ipState = ASSIGNED;
//				hdlDiscover(DHCPDISCOVERFROMCACHE);
//			}
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
	printf("%s\n",__FUNCTION__);
	cacheId = getIpFromCache();
	printf("\ncacheId=%d", cacheId);

	if(cacheId < 0)
	{
		printf("cache <0");

		//TODO Commit cache(refreshCache) into db, if full
		if(cacheId == -1){
			refreshCache();
			cacheId = getIpFromCache();
			//Can modify request for previously assigned IP
			if(cacheId < 0){
				spdUpdate();
			}
		}
		hdlCache(event);
//		hdlDiscover(DHCPDISCOVER);
		cacheId = 0;

	}
	printf("\ncacheId = %d ", cacheId);

	time_t currentTime;
	currentTime = time(NULL);

	ip[cacheId].ipState = ASSIGNED;
	ip[cacheId].timestamp = currentTime;

	printf("\n IP Assigned = %s ", ip[cacheId].ip_addr);
	printf("\n IP timestamp = %d ", ip[cacheId].timestamp);
	printf("\n IP ipState = %d ", ip[cacheId].ipState);

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
