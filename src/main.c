#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sqlite3.h"
#define VERSION "0.02"
#define INI_FILE "../file/test.ini"
#define DB_FILE "test.db"

/*set line in sqlite*/
static void set_line_sqlite(char *front, char *last, sqlite3 *db)
{
	int res = 0;
	char cmd[128] = "" ;
	char *errmsg = NULL;

	last[strlen(last) - 1] = '\0';//deleted the end of string
	sprintf(cmd,"insert into student(front,last)values(\"%s\",\"%s\")",front,last);
	res = sqlite3_exec(db,cmd,NULL,NULL,&errmsg);
	if (res != SQLITE_OK)
		return;
}

static int token_for_sqlite(char *line, sqlite3 *db)
{
	char *front = NULL;
	char *last  = NULL;
	
	assert(line);

	front = strtok(line,"=");

	if (front != NULL)
	{	
		last = strtok(NULL,"=");
		if (last != NULL)
			set_line_sqlite(front,last,db);
		else
			return -1;
	}
	else
		return -1;
		
	return 0;
}

/*read ini and set in sqlite*/
static int read_ini_for_sqlite(sqlite3 *db)
{
	FILE *file = NULL;
	char line[128] = "";
	int res = 0;	
	
	//open ini file as descriptor
	file = fopen("../file/test.ini","r");
	if (NULL == file)
	{
		perror("Error in fopen");
		return -1;
	}

	//read each line of ini file
	while(fgets(line,128,file) != NULL)
	{
		if (strstr(line,"=") != NULL)
		{
			res = token_for_sqlite(line,db);	
			if (res == -1)
				return -1;
		}
		else
			continue;
	}//end of while
	fclose(file);
	return 0;
}


int main(int argc, char **argv)
{
	sqlite3 *db = NULL;
	char *errmsg = NULL;
	int res = 0;
	char init[128] = "create table student(front text NOT NULL, last text NOT NULL)";
	res = sqlite3_open(DB_FILE,&db);
	if (res == -1)
		return -1;
	res = sqlite3_exec(db,init,NULL,NULL,&errmsg);
	if (res == -1)
		return -1;

	printf("The version is %s@ add A design\n",VERSION);
	read_ini_for_sqlite(db);
	return 0;
}
