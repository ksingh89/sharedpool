#include <stdio.h>
#include "sharedPool.h"
#include "hdlDHCP.h"
#include "hdlCache.h"

extern int hdlCache(int);

int hdlDHCP(event)
{
	int x;
	printf("inside hdlDHCP");
	switch(event)
	{
		case DHCPDISCOVER:
			hdlDiscover();
			break;
		case DHCPREQUEST:
			hdlRequest();
			break;
		case DHCPDECLINE:
			hdlDecline();
			break;
	}
	return 1;
}

int hdlDiscover()
{
	int event = 0;
	printf("inside hdlDiscover");
//	transfers the call to the cache thread for processing
	hdlCache(event);
	return 1;
}

int hdlRequest()
{
	int event = 1;
	printf("inside hdlRequest");
//	transfers the call to the cache thread for processing
	hdlCache(event);
	return 1;
}

int hdlDecline()
{
	int event = 1;
	printf("inside hdlDecline");
//	transfers the call to the cache thread for processing
	hdlCache(event);
	return 1;
}
