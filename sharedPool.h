#define PORT_LISTEN 6050
#define BUFSIZE 2048

enum state
{
	INIT_MT = 0,
	CONFIG_MT,
	PROC_MT
};



struct dhcpDiscover
{
	int a;
};

struct dhcpOffer
{
	int c;
};

struct dhcpRequest
{
	int b;
};

struct dhcpAck
{
	int d;
};

int cacheId;
unsigned int cacheAssignId;
unsigned int cacheInuseId;
