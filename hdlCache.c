#include <stdio.h>
#include "sharedPool.h"
#include "hdlCache.h"
#include "spd.h"

int ip[10];

int hdlCache(event)
{
	int x;
	printf("inside hdlCache");
	initHdlCacheThread();
	switch(event)
		{
			case IPALLOCATION:
				ipAllocation();
				break;
			case IPDEALLOCATION:
				ipDeallocation();
				break;
			case IPDECLINE:
				ipDecline();
				break;
		}
	return 1;
}

int initHdlCacheThread()
{
	printf("Inside initHdlCacheThread");
	return 1;
}

int ipAllocation()
{
	printf("inside ipAllocation");
//	Database connectivity
	if(!spdConnect())
	{
		printf("\nERROR!!");
		return 0;
	}
	return 1;
}

int ipDeallocation()
{
	printf("inside ipDeAllocation");
	if(!spdDisconnect())
	{
		printf("\nERROR!!");
		return 0;
	}
	return 1;
}

int ipDecline()
{
	printf("inside ipDecline");
	if(!spdConnect())
	{
		printf("\nERROR!!");
		return 0;
	}
//	resend the ip in the pool

	if(!spdDisconnect())
	{
		printf("\nERROR!!");
		return 0;
	}
	return 1;
}
