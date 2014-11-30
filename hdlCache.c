#include <stdio.h>
#include "sharedPool.h"
#include "hdlCache.h"
#include "spd.h"
#include "ssp.h"

//int ip[10];
extern struct IP_ADDR ip[CACHEVALUE];
//int hdlCache(int event, char* ip)
int hdlCache(int event)
{
	int x;
//	char *ipCache;
//	ipCache = ip;
	printf("%s\n",__FUNCTION__);
//	initHdlCacheThread();
	switch(event)
		{
			case IPALLOCATION:
//				ipAllocation(ipCache);
				ipAllocation();
				break;
			case IPCOMMIT:
				ipCommit();
				break;
			case IPDECLINE:
				ipDecline();
				break;
			case IPDEALLOCATION:
				ipDeallocation();
				break;
			case IPDISCOVERFROMCACHE:
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
//	char* ipAllocation;
//	ipAllocation = ip;
	printf("%s\n",__FUNCTION__);
//	Database connectivity
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
	ip[cacheId].ipState = ASSIGNED;
//	ip = ipAllocation;
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
int ipCommit()
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
	ip[cacheId].ipState = INUSE;
	return 1;
}

int ipFromCache()
{
//	char* ipAllocation;
//	ipAllocation = ip;
	ip[cacheId].ipState = ASSIGNED;
//	ip = ipAllocation;
	return 1;
}
