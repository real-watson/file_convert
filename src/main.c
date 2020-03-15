#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define VERSION "0.02"

/*set line in sqlite*/

static int token_for_sqlite(char *line)
{
	char *front = NULL;
	char *last  = NULL;
	
	assert(line);

	front = strtok(line,"=");

	if (front != NULL)
	{	
		last = strtok(NULL,"=");
		if (last != NULL)
			printf("%s|%s\n",front,last);
		else
			return -1;
	}
	else
		return -1;
		
	return 0;
}

/*read ini and set in sqlite*/
static int read_ini_for_sqlite()
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
			res = token_for_sqlite(line);	
			if (res == -1)
				return -1;
		}
		else
			continue;
	}//end of while
	return 0;
}


int main(int argc, char **argv)
{
	printf("The version is %s@ add A design\n",VERSION);
	read_ini_for_sqlite();
	return 0;
}
