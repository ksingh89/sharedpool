#include <stdio.h>
#include <string.h>

#include "sharedPool.h"
#include "hdlCache.h"
#include "spd.h"
#include "ssp.h"
#include "time.h"

//int ip[10];
extern struct IP_ADDR ip[CACHEVALUE];
//int hdlCache(int event, char* ip)
int hdlCache(struct sspMessage* request)
{
	int x;
	struct sspMessage* req = NULL;
	req = request;
//	char *ipCache;
//	ipCache = ip;
	printf("%s\n",__FUNCTION__);
//	initHdlCacheThread();
	switch(req->event)
		{
			case IPALLOCATION:
//				ipAllocation(ipCache);
				ipAllocation();
				break;
			case IPCOMMIT:
				ipCommit(req);
				break;
			case IPDECLINE:
				ipDecline();
				break;
			case IPDEALLOCATION:
				ipDeallocation();
				break;
			case IPDISCOVERFROMCACHE:
				//case not used
				ipFromCache();
				break;
		}
//	ip = ipCache;
	return 1;
}

int initHdlCacheThread()
{
	printf("%s\n",__FUNCTION__);
	return 1;
}

//int ipAllocation(char* ip)
int ipAllocation()
{
	//struct sspMessage* req=NULL;
//	char* ipAllocation;
//	ipAllocation = ip;
	printf("%s\n",__FUNCTION__);
//	Database connectivity
	//req = request;
	if(!spdConnect())
	{
		printf("\nERROR!!");
		return 0;
	}
//	else if(!spdFetch(ip))
	else if(!spdFetch())
	{
		printf("\nERROR!!");
		return 0;
	}
	
	cacheId = 0;
	//ip[cacheId].xid = req->xid;
	return 1;
}

int ipDeallocation()
{
	printf("%s\n",__FUNCTION__);
	if(!spdConnect())
	{
		printf("\nERROR!!");
		return 0;
	}
	//	resend the ip in the pool

	if(!spdUpdate())
	{
		printf("\nERROR!!");
		return 0;
	}

	if(!spdDisconnect())
	{
		printf("\nERROR!!");
		return 0;
	}
	return 1;
}

int ipDecline()
{
	printf("%s\n",__FUNCTION__);
	if(!spdConnect())
	{
		printf("\nERROR!!");
		return 0;
	}
//	resend the ip in the pool

	if(!spdUpdate())
	{
		printf("\nERROR!!");
		return 0;
	}
	if(!spdDisconnect())
	{
		printf("\nERROR!!");
		return 0;
	}
	return 1;
}
int ipCommit(struct sspMessage* request)
{
	printf("%s\n",__FUNCTION__);
	if(!spdConnect())
	{
		printf("\nERROR!!");
		return 0;
	}
//	resend the ip in the pool

	if(!spdCommit())
	{
		printf("\nERROR!!");
		return 0;
	}
	//for() check for the values requested IP and Transaction ID. if it matches then put it inUse and mark it NULL
	ip[cacheId].ipState = INUSE;
	return 1;
}
//depricated
int ipFromCache()
{
	printf("%s\n",__FUNCTION__);
//	char* ipAllocation;
//	ipAllocation = ip;
	ip[cacheId].ipState = ASSIGNED;
//	ip = ipAllocation;
	return 1;
}

int getIpFromCache(){
	printf("\n%s",__FUNCTION__);
	int i=0;
	//have a good check for null
	if(strlen(ip[0].ip_addr) == 0)
		return -2;
	while(i<CACHEVALUE)
	{
		if(ip[i].ipState == CACHE )
		{
			printf("\nip[i].ip_addr = %s",ip[i].ip_addr );
			return i;
		}
		i++;
	}
	return -1;
}

void refreshCache(){

	printf("%s\n",__FUNCTION__);
	int i=0;

	time_t currentTime;
	currentTime = time(NULL);
	while(i<CACHEVALUE)
	{
		printf("\ncurrent time %ld && timestamp %ld\n",currentTime, ip[i].timestamp);
		if(currentTime - ip[i].timestamp > 3 && ip[i].ipState == ASSIGNED){
			//TODO uncomment it
			ip[i].ipState = CACHE;
		}
		i++;
	}

}


