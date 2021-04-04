#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX_PATH 256

int FindFile(char *start_dir, char *target, char *path);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);



int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Usage: %s <start_dir> <target_file>\n", argv[0]);
		return 0;
	}	
	char *start_dir = argv[1];
	char *target = argv[2];
	char path[MAX_PATH] = "";
	int ret = FindFile(start_dir, target, path);

	if(ret) 
		printf("path = %s\n", path);
	else
		printf("Cannot find %s\n", target);
	
	return 0;
}


int FindFile(char *start_dir, char *target, char *path)
{
	printf("finding file\n");
}
