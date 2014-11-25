#include <stdio.h>
#include "sharedPool.h"
#include "hdlCache.h"

extern int ipAllocation(void);
extern int ipDeallocation(void);
extern int ipDecline(void);

int hdlCache(event)
{
	int x;
	printf("inside hdlCache");
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

int ipAllocation()
{
	printf("inside ipAllocation");
	return 1;
}

int ipDeallocation()
{
	printf("inside ipDeAllocation");
	return 1;
}

int ipDecline()
{
	printf("inside ipDecline");
	return 1;
}
