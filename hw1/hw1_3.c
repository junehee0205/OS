#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
 
#define MAX_CMD 2048
#define MAX_ARG 256
void ParseCommand (char *command, int *argc , char *argv[]);

int main()
{
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1] = 0; // for safety
	int argc = 0;
	char *argv[MAX_ARG] = {NULL};
	while(1){
		printf("$ ");
		fgets(command, MAX_CMD-1, stdin);
		printf("%s", command);
		command[strlen(command)-1] = 0; // trim \r

		if(strcmp (command, "quit") == 0 || strcmp (command, "exit") == 0) break;
		
		ParseCommand(command, &argc , argv);
		
		printf("argc = %d\n", argc);
		for(int i = 0; i < argc; i++){
			printf("argv[%d] = %s\n", i, argv[i]);}
		printf ("argv[%d] = %p\n", argc, argv[argc]); // argv argc ] must be NULL}	
}

	printf("Bye!\n");
	return 0;
}


void ParseCommand (char *command, int *argc , char *argv[])
{

	*argc = 0;
	int i=0;
	char *ptr = strtok(command, " ");	
	while(ptr != NULL){
		argv[i] = ptr;
		ptr = strtok(NULL, " ");
		i++;
		*argc+=1;
	}
}



