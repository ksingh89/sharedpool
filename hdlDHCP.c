#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sharedPool.h"
#include "hdlCache.h"
#include "spd.h"
#include "ssp.h"
#include "hdlDHCP.h"

//extern int hdlCache(int, char*);
extern struct IP_ADDR ip[CACHEVALUE];
extern int hdlCache(struct sspMessage*);
extern int getIpFromCache();
extern int cacheId;

void hdlDHCP(void* ptr)
{
	int msgType, x;
	char *ip1;
	struct sspMessage *req;
	req = (struct sspMessage *)ptr;
//	enum stateHdlDhcp state;
//	initHdlDhcpThread();
	printf("%s\n",__FUNCTION__);
	printf("event = %d",req->messageType);
	switch(req->messageType)
	{
		case DHCPDISCOVER:
			printf("\nIn DHCPDISCOVER..");
			hdlDiscover(req);
//			else
//			{
//				//ip[cacheId].ipState = ASSIGNED;
//				hdlDiscover(DHCPDISCOVERFROMCACHE);
//			}
			break;
		case DHCPREQUEST:
			//x = DHCPREQUEST;
//			Can modify the request for previously assigned IP
			hdlRequest(req);
			break;
		case DHCPDECLINE:
			//x = DHCPDECLINE;
			hdlDecline(DHCPDECLINE);
			break;
	}
	//free(ptr);
	pthread_exit(NULL);
}

int initHdlDhcpThread()
{
	printf("%s\n",__FUNCTION__);
	return 1;
}
//int hdlDiscover(int event, char* ip)
int hdlDiscover(struct sspMessage* request)
{
	struct sspMessage* req = NULL;
	req = request;
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
		else
		{
		hdlCache(req);
//		hdlDiscover(DHCPDISCOVER);
		cacheId = 0;
		}

	}
	printf("\ncacheId = %d ", cacheId);

	time_t currentTime;
	currentTime = time(NULL);

	ip[cacheId].ipState = ASSIGNED;
	ip[cacheId].timestamp = currentTime;
	ip[cacheId].xid	= req->xid;

	printf("\n IP Assigned = %s ", ip[cacheId].ip_addr);
	printf("\n IP timestamp = %ld ", ip[cacheId].timestamp);
	printf("\n IP ipState = %d ", ip[cacheId].ipState);
	printf("\n IP xid = %ld ", ip[cacheId].xid);

//	ip = ipdis;
	return 1;
}

int hdlRequest(struct sspMessage *request)
{
	//int event = 1;
	struct sspMessage *req=NULL;
	req = request;
	printf("%s\npacket :%d %d %s %u",__FUNCTION__,req->messageType, req->event, req->ip, req->xid);
//	transfers the call to the cache thread for processing
	hdlCache(req);
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
