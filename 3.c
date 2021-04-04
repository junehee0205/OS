#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#define MAX_SIZE 1024
void do_ls(char[], char[]);
char *getcwd(char *buf, size_t size);


int main( int ac, char *av[] )
{
        printf("%s\n", av[1]);
        do_ls(av[1], av[1]);
}
void do_ls( char path[], char dirname[] ) { // recursive func
    DIR *dir_ptr;
    struct dirent *direntp;
    char buffer[MAX_SIZE] = "";
    strcat(buffer, path);
char cpath[MAX_SIZE];
	printf("path:%s", buffer);
        chdir(dirname);
//	printf("%s", getcwd(cpath, MAX_SIZE));
        while((direntp = readdir(dir_ptr)) != NULL) {
            if(opendir(direntp->d_name) != NULL) {
                if(strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
                    strcat(buffer, "/");
                    strcat(buffer, direntp->d_name);
//                    printf("%s\n", buffer);
                    do_ls(buffer, direntp->d_name);
                    strcpy(buffer, dirname);
                    if(strcmp(buffer, ".") != 0) {
                        strcpy(buffer, "./");
                        strcat(buffer, dirname);
                    }
                }
            }
            else {
          //      printf("%s/%s\n", buffer, direntp->d_name);
                if(strcmp(buffer, ".") != 0) {
                    chdir("..");
                    strcpy(buffer, ".");
                }
            }
        }
    }
