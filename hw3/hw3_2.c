#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>

time_t time( time_t *timer );
char *ctime( const time_t *timer);
void nocommandline();
void fileinfo(char *filename);


int main(int argc , char *argv[])
{		
	if(argc == 1) nocommandline();
	else fileinfo(argv[1]);
	return 0;
}

void nocommandline()
{
	printf("User and Process info:\n");
	printf("\t getuid() = %d\n", getuid());	
	printf("\t getpid() = %d\n", getpid());
	printf("\t getppid() = %d\n\n", getppid());

	struct utsname un;
	uname(&un);
	printf("Kernel info:\n");
	printf("\tsysname = %s\n", un.sysname);
	printf("\tnodename = %s\n", un.nodename);
	printf("\trelease = %s\n", un.release);
	printf("\tversion = %s\n", un.version);
	printf("\tmachine = %s\n\n", un.machine);

	struct sysinfo info;
	sysinfo(&info);
	printf("System info:\n");
	printf("\tuptime = %ld\n", info.uptime);
	printf("\ttotalram = %ld\n", info.totalram);
	printf("\tfreeram = %ld\n", info.freeram);
	printf("\tprocs = %d\n", info.procs);
}

void fileinfo(char *filename)
{
	printf("Permission of file a.out\n");
	printf("\tpermission to read: %d\n", access( filename, R_OK ) == 0 );
	printf("\tpermission to write: %d\n", access( filename, W_OK ) == 0 );
	printf("\tpermission to execute: %d\n", access( filename, X_OK ) == 0 );

	struct stat finfo;
	stat(filename, &finfo);	

	printf("\nstat of file %s\n",filename);
	printf("\tst_dev = %ld\n",finfo.st_dev);
	printf("\tst_ino = %ld\n",finfo.st_ino);
	printf("\tst_mode = %o\n",finfo.st_mode);
	printf("\tst_uid = %d\n",finfo.st_uid);
	printf("\tst_gid = %d\n",finfo.st_gid);
	printf("\tst_size = %ld\n",finfo.st_size);
//	printf("\tst_atime = %d/%d/%d %d:%d:%d\n",localtime(&finfo.st_atime).tm_year+1900,localtime(&finfo.st_atime).tm_mon+1,localtime(&finfo.st_atime).tm_mday,localtime(&finfo.st_atime).tm_hour,localtime(&finfo.st_atime).tm_min,localtime(&finfo.st_atime).tm_sec);
	printf("\tst_atime = %d/%d/%d %d:%d:%d\n",localtime(&finfo.st_atime)->tm_year+1900,localtime(&finfo.st_atime)->tm_mon+1,localtime(&finfo.st_atime)->tm_mday,localtime(&finfo.st_atime)->tm_hour,localtime(&finfo.st_atime)->tm_min,localtime(&finfo.st_atime)->tm_sec);
	printf("\tst_mtime = %d/%d/%d %d:%d:%d\n",localtime(&finfo.st_mtime)->tm_year+1900,localtime(&finfo.st_mtime)->tm_mon+1,localtime(&finfo.st_mtime)->tm_mday,localtime(&finfo.st_mtime)->tm_hour,localtime(&finfo.st_mtime)->tm_min,localtime(&finfo.st_mtime)->tm_sec);
	printf("\tst_mtime = %d/%d/%d %d:%d:%d\n",localtime(&finfo.st_ctime)->tm_year+1900,localtime(&finfo.st_ctime)->tm_mon+1,localtime(&finfo.st_ctime)->tm_mday,localtime(&finfo.st_ctime)->tm_hour,localtime(&finfo.st_ctime)->tm_min,localtime(&finfo.st_ctime)->tm_sec);
//	printf("\tst_ctime = %d/%d/%d %d:%d:%d\n",localtime(&finfo.st_ctime)->tm_sec);
//	struct tm *mt = localtime(&finfo.st_mtime);
//	struct tm *ct = localtime(&finfo.st_ctime);
/*	printf("%d/%d/%d %d:%d:%d\n", at->tm_year+1900, at->tm_mon+1, at->tm_mday, at->tm_hour, at->tm_min, at->tm_sec);
	printf("%d/%d/%d %d:%d:%d\n", mt->tm_year+1900, mt->tm_mon+1, mt->tm_mday, mt->tm_hour, mt->tm_min, mt->tm_sec);
	printf("%d/%d/%d %d:%d:%d\n", ct->tm_year+1900, ct->tm_mon+1, ct->tm_mday, ct->tm_hour, ct->tm_min, ct->tm_sec);
*/
}

