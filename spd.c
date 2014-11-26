#include<stdio.h>
#include "spd.h"
#include "sqlite3.h"

int isOpenDB = FALSE;
sqlite3 *dbfile;

int spdIpAlloc()
{
	printf("inside spdIpAlloc");
	return 1;
}

int spdConnect()
{
//	connect sqlite3
	if ( sqlite3_open(DB, &dbfile) == SQLITE_OK )
	{
		isOpenDB = TRUE;
		return TRUE;
	}

	return FALSE;
}

int spdDisconnect()
{
	if ( isOpenDB == TRUE )
	{
		sqlite3_close(dbfile);
		return 1;
	}
	else
		return 0;
}
