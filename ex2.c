#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX_CMD 2048
#define MAX_ARG 256


int main()
{
	DIR *dir = NULL;
	struct dirent *ls = NULL;	

	dir = opendir(".");
	while((ls = readdir(dir)) != NULL){
		if(ls->d_type ==4 ){
			printf("%s [directory]\n", ls->d_name);}
		else{
			printf("%s\n", ls->d_name);}
	}
	return 0;
}





