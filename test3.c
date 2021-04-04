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
	
	DIR *dir = NULL;
	struct dirent *ls = NULL;	
	char buf[MAX_PATH] = "";
	char upbuf[MAX_PATH] = "";
	char cpath[MAX_PATH];	

	chdir(start_dir);
	strcat(path, getcwd(cpath, MAX_PATH));
	strcat(buf, getcwd(cpath, MAX_PATH));
	printf("start dir: %s\n",buf);
	dir = opendir(start_dir);
	while((ls = readdir(dir)) != NULL){
		if(strcmp(ls->d_name, target) == 0){
			strcat(path, "/");
			strcat(path, target);
			chdir(path);
			return 1;}
	//	else if(ls->d_type == 4){
	//		strcat(buf, "/");
	//		strcat(buf, ls->d_name);
	//		chdir(buf);
	//		FindFile(buf, target, path);
	//		}
	}
	return 0;
}
