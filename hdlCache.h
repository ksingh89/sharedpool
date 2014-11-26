enum stateHdlCache
{
	INIT_CT =0,
	CONFIG_CT,
	PROC_CT
};

#define IPALLOCATION 0
#define IPDEALLOCATION 1
#define IPDECLINE 2

int ipAllocation(void);
int ipDeallocation(void);
int ipDecline(void);
