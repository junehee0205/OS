#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#define MAX_SIZE 1024
void do_ls(char[], char[]);
void print_error(int, char[]);
int main( int ac, char *av[] )
{
    if( ac == 1 ) {
        print_error(1, NULL);
    }
    else {
        printf("%s\n", av[1]);
        do_ls(av[1], av[1]);
    }
}
void do_ls( char path[], char dirname[] ) { // recursive func
    DIR *dir_ptr;
    struct dirent *direntp;
    char buffer[MAX_SIZE] = "";
    strcat(buffer, path);
    if((dir_ptr = opendir(dirname)) == NULL) {
        print_error(2, dirname);
    }
    else {
        chdir(dirname);
        while((direntp = readdir(dir_ptr)) != NULL) {
            if(opendir(direntp->d_name) != NULL) {
                if(strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
                    strcat(buffer, "/");
                    strcat(buffer, direntp->d_name);
                    printf("%s\n", buffer);
                    do_ls(buffer, direntp->d_name);
                    strcpy(buffer, dirname);
                    if(strcmp(buffer, ".") != 0) {
                        strcpy(buffer, "./");
                        strcat(buffer, dirname);
                    }
                }
            }
            else {
                printf("%s/%s\n", buffer, direntp->d_name);
                if(strcmp(buffer, ".") != 0) {
                    chdir("..");
                    strcpy(buffer, ".");
                }
            }
        }
    }
}
void print_error(int error_num, char dirname[]) {
    switch(error_num) {
        case 1:
            printf("usage : find [-H | -L | -P] [-EXdsx] [-f path] path ... [expression]\n");
            printf("        find [-H | -L | -P] [-EXdsx] -f path [path ...] [expression]\n");
            break;
        case 2:
            fprintf(stderr, "error: cannot open %s\n", dirname);
            break;
    }
}
