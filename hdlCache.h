
enum stateHdlCache
{
	INIT_CT =0,
	CONFIG_CT,
	PROC_CT
};

//int ipAllocation(char*);
int ipAllocation(void);
int ipDeallocation(void);
int ipDecline(void);
int ipFromCache(void);
int getIpFromCache();
void refreshCache(void);
