#include<stdio.h>
#include<string.h>
#include "spd.h"
#include "sqlite3.h"

int isOpenDB = FALSE;
sqlite3 *dbfile;
struct IP_ADDR ip[10];

extern struct IP_ADDR ip[10];
//extern unsigned int cacheId;

int spdIpAlloc()
{
	printf("%s\n",__FUNCTION__);
	return 1;
}

int spdConnect()
{
	printf("%s\n",__FUNCTION__);
//	connect sqlite3
	if ( sqlite3_open(DB, &dbfile) == SQLITE_OK )
	{
		//isOpenDB = TRUE;
		return TRUE;
	}

	return FALSE;
}

//int spdFetch(char* ipDispatch)
int spdFetch()
{
	int intfetch,i;	
	char* sql = "SELECT * from mac_ip";
	sqlite3_stmt *statement = NULL;
	const char *value;
	//fetching the IP addresses from the DB
	//Once the connection is successful get the ip addr from DB.	
	/* Execute SQL statement */
	printf("%s\n",__FUNCTION__);
	intfetch = sqlite3_prepare(dbfile, sql, 128, &statement, NULL);

	for(i=0;i<3;i++)
	{
		intfetch = sqlite3_step(statement);

		if(SQLITE_ROW != intfetch)
		{
			printf("***sqlite3_step ERROR!!! %s(%d)***", sqlite3_errmsg(dbfile), intfetch);
			return 0;
		}
		//char ipaddr[100]={0};
		value = sqlite3_column_text(statement, 1);
		strncpy(ip[i].ip_addr, value, 100);
		//ip[i].ip_addr[0]=ipaddr;
		printf("%s\n",ip[i].ip_addr);
		ip[i].ipState = CACHE; //CACHE = 1
	}
//	memcpy(ipDispatch, ip[0].ip_addr, sizeof ip[0].ip_addr);
	return 1;
}

int spdDisconnect()
{
	printf("%s\n",__FUNCTION__);
	if ( isOpenDB == TRUE )
	{
		sqlite3_close(dbfile);
		return 1;
	}
	else
		return 0;
}

int spdCommit()
{
	printf("%s\n",__FUNCTION__);
//	connect sqlite3
//	if ( sqlite3_open(DB, &dbfile) == SQLITE_OK )
//	if(here we need commit the IP assigned to DB)
	{
		//isOpenDB = TRUE;
		return TRUE;
	}

	return FALSE;
}

int spdUpdate()
{
	printf("%s\n",__FUNCTION__);
	// UPDATE PROCEDURE
//	int intfetch,i;
//	char* sql = "SELECT * from mac_ip";
//	sqlite3_stmt *statement = NULL;
//	const char *value;
//	//fetching the IP addresses from the DB
//	//Once the connection is successful get the ip addr from DB.
//	/* Execute SQL statement */
//	intfetch = sqlite3_prepare(dbfile, sql, 128, &statement, NULL);
//
//	for(i=0;i<3;i++)
//	{
//		intfetch = sqlite3_step(statement);
//
//		if(SQLITE_ROW != intfetch)
//		{
//			printf("***sqlite3_step ERROR!!! %s(%d)***", sqlite3_errmsg(dbfile), intfetch);
//			return 0;
//		}
//		//char ipaddr[100]={0};
//		value = sqlite3_column_text(statement, 1);
//		strncpy(ip[i].ip_addr, value, 100);
//		//ip[i].ip_addr[0]=ipaddr;
//		printf("%s\n",ip[i].ip_addr);
//	}
//	memcpy(ipDispatch, ip[0].ip_addr, sizeof ip[0].ip_addr);
	return 1;
}
