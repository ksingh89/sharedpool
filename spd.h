#define SPD 1
#define TRUE 1
#define FALSE 0
#define CACHEVALUE 3
#define DB "network_config"

//unsigned int cacheId;
//unsigned int cacheAssignId;

enum ip_state
{
	CACHE=1,
	ASSIGNED,
	INUSE
};
struct IP_ADDR
{
	char ip_addr[255];
	enum ip_state ipState;//int lease;
	long int timestamp;
	unsigned int xid;
	char ip_addr_4[4];
};
