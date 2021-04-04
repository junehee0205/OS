#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


int main()
{
	DIR *dir = NULL;
	struct dirent *ls = NULL;	

	dir = opendir(".");
	while((ls = readdir(dir)) != NULL){
		if(ls->d_type ==4 && strcmp(ls->d_name, ".") != 0 && strcmp(ls->d_name, "..") != 0 ){
			printf("%s [directory]\n", ls->d_name);}
		else{
			printf("%s\n", ls->d_name);}
	}
	closedir(dir);
	return 0;
}





