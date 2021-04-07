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
int FindFile(char *start_dir, char *target, char *path );

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


int FindFile(char *start_dir, char *target, char *path ) { // recursive func
    	DIR *dir;
    	struct dirent *ls;
  	char buf[MAX_PATH] = "";
	char cpath[MAX_PATH];
   	strcat(buf, start_dir);
        chdir(start_dir);
	if((dir = opendir(start_dir))== NULL){
		return 0;}
	else{
		while((ls = readdir(dir)) != NULL) {
			if(strcmp(ls->d_name,target) == 0){
			strcpy(path, getcwd(cpath, MAX_PATH));
			strcat(path, "/");
			strcat(path, target);
			return 1;
			}
		
		else  if( ls->d_type ==  4  && strcmp(ls->d_name, ".") != 0 && strcmp(ls->d_name, "..") != 0) {
			if(strcmp(buf, "/") != 0)strcat(buf, "/");{
                    		strcat(buf, ls->d_name);
			if(FindFile(buf, target, path) == 0){
				chdir("..");
				strcpy(buf, getcwd(cpath, MAX_PATH));
			}
			else{
			return 1; 
                    	}
                }
	}
	}	
	closedir(dir);
	return 0;
	}
}
