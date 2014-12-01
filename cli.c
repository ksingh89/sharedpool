#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

enum msgty 
{
	DHCPDISCOVER=0,
	DHCPREQUEST,
	DHCPDECLINE
};
char* discover = "0.0.0.0";
char* request = "192.168.1.101";

struct sspMessage
{
        unsigned char messageType;
        unsigned char event;
        char ip[4];
        unsigned int xid;
};

int ip_asc2bytes(char bytes[], char* ip_address)
{
        printf("==>ip_asc2bytes, ip_address=%s strlen = %d\n", ip_address,strlen(ip_address));

    if(NULL == ip_address || strlen(ip_address) > 15 || strlen(ip_address) < 7)
    {
        printf("***IP address is invalid, ip_asc2bytes==>***");
        return 0;
    }

    char buff[4] = {0};
    int buff_index = 0;
    int ret = 0;
    int i = 0;
    for(i = 0; '\0' != ip_address[i]; i++)
    {
        if('.' == ip_address[i])
        {
            buff[4] = '\0';
            bytes[ret++] = atoi(buff);
            memset(buff, 0, 4);
            buff_index = 0;
        }

        if(ip_address[i] >= '0' && ip_address[i] <= '9')
        {
            buff[buff_index++] = ip_address[i];
        }
    }

    if(buff_index > 0)
    {
        buff[4] = '\0';
        bytes[ret++] = atoi(buff);
    }
    printf("\nip_asc2bytes==>\n");
    return ret;
}


int main()
{
	int csd, val;
	socklen_t recvVal;
        int msgtype;
	char temp[24];
	struct sspMessage dis;
	struct sspMessage req;
	struct sspMessage dec;
	struct sspMessage disRes;
	struct sockaddr_in srvadr;
 	char buffer[255];
	socklen_t len = sizeof srvadr; 

	csd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&srvadr, 0, sizeof srvadr);
	srvadr.sin_family = AF_INET;
	srvadr.sin_addr.s_addr = inet_addr("127.0.0.1");
	srvadr.sin_port = htons(6050);
	//val = connect(csd, (struct sockaddr*)&srvadr, sizeof srvadr);

	//if(val == -1)
	//{
	//	printf("Error Connecting client\n");
	//}
	//else
	//{
	//	printf("Successful Connect\n");
	//}
	//memset(&val,0,sizeof val);
	do
	{
		printf("\nEnter the message type::\n");
		scanf("%d",&msgtype);
		switch(msgtype)
		{
			case DHCPDISCOVER:
		        dis.messageType = DHCPDISCOVER;
		        dis.event= 0;
        		//memcpy(dis.ip, request->ciaddr, sizeof(dis.ip));
        		//memcpy(&dis.xid, &request->xid, sizeof(dis.xid));
			ip_asc2bytes(dis.ip, discover);
			dis.xid = 12345;

			val = sendto(csd, (void *)&dis, sizeof dis, 0, (struct sockaddr*)&srvadr, len);
			if(val < 0)
			{
				printf("Error Sending\n");
				return 0;
			}
			recvVal = recvfrom(csd, buffer,sizeof buffer,0,(struct sockaddr*)&srvadr, &len);
			printf("\nrecvVal %d %s\n",recvVal,buffer);
			//memcpy(disRes.ip, buffer, sizeof buffer);
			printf("\ndisRes.ip %s\n",buffer);
			break;
			case DHCPREQUEST:
		        req.messageType = DHCPREQUEST;
		        req.event= 1;
        		//memcpy(dis.ip, request->ciaddr, sizeof(dis.ip));
        		//memcpy(&dis.xid, &request->xid, sizeof(dis.xid));
			ip_asc2bytes(req.ip, request);
			req.xid = 12345;
			val = sendto(csd, (void *)&req, sizeof req, 0, (struct sockaddr*)&srvadr, sizeof srvadr);
			if(val < 0)
			{
				printf("Error Sending\n");
				return 0;
			}
			recvVal = recvfrom(csd, buffer,sizeof buffer,0,(struct sockaddr*)&srvadr, &len);
			//memcpy(disRes.ip, buffer, sizeof buffer);
			printf("\ndisRes.ip %s\n",buffer);
			break;
			case DHCPDECLINE:
			val = sendto(csd, (void *)&dec, sizeof dec, 0, (struct sockaddr*)&srvadr, sizeof srvadr);
			if(val < 0)
			{
				printf("Error Sending\n");
				return 0;
			}
			break;
			default:
			exit(0);
		}
	}
	while(msgtype >= 0 && msgtype < 3);
}
