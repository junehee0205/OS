#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX_CMD 2048
#define MAX_ARG 256
#define BUF_SIZE 1024

char buffer[BUF_SIZE];
int buffer_size=0;
int buffer_pos=0;


void ParseCommand (char *command, int *argc , char *argv[]);
int mkdir (const char *path, mode_t mode);
int ReadTextLine(int fd, char str[], int max_len)
{
	int i=0;
	int j=0;
	int ret = 0;

	if(lseek(fd, 0, SEEK_CUR) == 0 )
		{buffer_pos = buffer_size = 0;}
	while(j<max_len-1){
		if(buffer_pos == buffer_size){
			buffer[0] = 0;
			buffer_size = read(fd, buffer, BUF_SIZE);
			buffer_pos = 0;
		}
		if(buffer_size == 0){
			if(j==0)
			{ret = EOF;}
			break;
		}
		while(j<max_len-2 && buffer_pos < buffer_size){
			str[j++] =  buffer[buffer_pos++];
			if(str[j-1] == '\0' || str[j-1] == 10){
				j--;
				max_len = j;
				break;
			}
		}
	}
	
	str[j] = 0;

	return ret;
}

void ParseCommand(char *command, int *argc , char *argv[]){

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

int main(int argc, char *argv[])
{
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1] = 0; // for safety
	int fd = open(argv[1], O_RDONLY|O_CREAT);
	char path[BUF_SIZE];
	int i = 0;
	char com[BUF_SIZE];
	while(1){
		if(ReadTextLine(fd, command, MAX_ARG) == EOF) {break;}
			printf("command = [%s]\n", command);
			char *newargv[MAX_ARG] = {NULL};
			int newargc = 0;
			strcpy(com, command);
			ParseCommand(command, &newargc , newargv);
			if(strstr(newargv[0], "cd") != NULL){
				chdir(newargv[1]);
				printf("\n");
			}	
			else if(strcmp(&command[0], "#") == 0) printf("\n");
			else{
				pid_t pid = fork();
				if(pid>0){
				execvp("_FILE_", argv[1]);
				wait(0);
				}
				else if(pid==0){
					system(com);
					printf("\n");
					return 0;
				}	
			}
		}
	close(fd);
	return 0;
}







