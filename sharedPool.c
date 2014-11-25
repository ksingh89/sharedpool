#include <stdio.h>
#include <pthread.h>
#include "sharedPool.h"
#include "hdlDHCP.h"
#include "hdlCache.h"

extern int hdlDHCP(void);
extern int hdlCache(void);

int main()
{
	int id=0;
//	handler thread id and cache thread id and main thread id
	pthread_t hdlTid, cacheTid;
	printf("Inside Shared Pool main");
//	create threads to segregate work items
//	creating handler thread
	pthread_create(&hdlTid,NULL, (void*)&hdlDHCP, NULL);
//	creating cache thread
	pthread_create(&cacheTid, NULL, (void*)&hdlCache, NULL);
//	initSharedPool();
	while(1)
	{
		switch(id)
		{
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
	}
	return 0;
}
