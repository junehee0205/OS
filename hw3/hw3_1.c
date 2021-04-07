#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

time_t time( time_t *timer );
char *ctime( const time_t *timer);

int main(int argc , char *argv[])
{		
	time_t ntime;
	struct tm *ct;
	time(&ntime);
	printf("%ld\n", ntime);
	ct = localtime(&ntime);

	double sec = atof(argv[1]);
	int chour = ct->tm_hour;
	int cmin = ct->tm_min;
	int csec = ct->tm_sec;
				

	printf("current date =  %d/%d/%d\n",ct->tm_year+1900, ct->tm_mon+1, ct->tm_mday);
	printf("current time = %d:%d:%d\n\n", chour, cmin, csec);

	printf("waiting for %f sec using usleep()\n\n", sec);

	struct timeval ctime;
	struct timeval atime;

	gettimeofday(&ctime, NULL);
	
	usleep(sec*1000*1000);
	
	gettimeofday(&atime, NULL);
	time_t etime;
	struct tm *at;
	time(&etime);
	at = localtime(&etime);

	printf("start_time = (%ld %ld), %d:%d:%d\n", ctime.tv_sec, ctime.tv_usec, chour,cmin,csec);
	printf("end_time = (%ld %ld), %d:%d:%d\n", atime.tv_sec, atime.tv_usec, at->tm_hour, at->tm_min, at->tm_sec);
	long double et = (atime.tv_sec-ctime.tv_sec+(atime.tv_usec-ctime.tv_usec)*0.000001);
	printf("elapsed time = %Lfsec\n", et);

	return 0;
}
