#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand (char *command, int *argc , char *argv[]);
int mkdir (const char *path, mode_t mode);
int rmdir(const char *path);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);

int main()
{
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1] = 0; // for safety
	int argc = 0;
	char *argv[MAX_ARG] = {NULL};
	char name[MAX_ARG];
	DIR *dir = NULL;
	struct dirent *ls = NULL;	

	while(1){
		printf("$ ");
		fgets(command, MAX_CMD-1, stdin);
		command[strlen(command)-1] = 0; // trim \r

		if(strcmp (command, "quit") == 0 || strcmp (command, "exit") == 0) break;
		
		ParseCommand(command, &argc , argv);
		if(strstr(argv[0], "mkdir") != NULL){
			mkdir(argv[1], 0755);
		}
		
		else if(strstr(argv[0], "rmdir") != NULL){
			rmdir(argv[1]);
		}

		else if(strstr(argv[0], "cd") != NULL){
			chdir(argv[1]);
		}

		else if(strstr(argv[0], "curdir") != NULL){
			printf("Current  Directory: %s\n", getcwd(name, MAX_ARG));
		}

		else if(strstr(argv[0], "ls") != NULL){
			system("ls");
		}
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



