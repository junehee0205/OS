#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 1024


void CPUInfo();
void MemInfo();
void AvgInfo();
char buffer[BUF_SIZE];
int buffer_size=0;
int buffer_pos=0;

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

void CPUInfo()
{	
	char buf[BUF_SIZE];
	int fd = open("../../proc/cpuinfo", O_RDONLY|O_CREAT);
		

	int cpu = 0;	
	while(ReadTextLine(fd,buf,BUF_SIZE) == 0){
	
		char name[20];
		char info[BUF_SIZE];
		
		sscanf(buf, "%[^':']: %[^\n]",name,info);

		if(cpu<2 && strstr(name, "cpu cores")){
			printf("%s: %s\n", name, info);
			cpu++;}
			
		if(cpu == 1 && strstr(name, "model name")){
			printf("%s: %s\n", name, info);
			cpu++;}
	}	FILE *fp = fopen("argv[1]", "r");	

	close(fd);
}

void MemInfo()
{
	char buf[BUF_SIZE];
	int fd = open("../../proc/meminfo", O_RDONLY|O_CREAT);
	
	while(ReadTextLine(fd,buf,BUF_SIZE) == 0){
	
		char name[20];
		char info[BUF_SIZE];

		sscanf(buf, "%[^':']:%[^\n]",name,info);

		if(strstr(name, "MemTotal"))
			printf("%s :%s\n", name, info);
	}
	close(fd);
}

void AvgInfo()
{
	char buf[BUF_SIZE];
	int fd = open("../../proc/loadavg", O_RDONLY|O_CREAT);
	
	while(ReadTextLine(fd,buf,BUF_SIZE) == 0){
	
		double  a1, a5, a15;

		sscanf(buf, "%lf %lf %lf",&a1,&a5,&a15);
		printf("loadavg1 = %lf\nloadavg5 = %lf\nloadavg15 = %lf\n", a1, a5, a15);	
	}
	close(fd);
}



int main(){

	CPUInfo();
	MemInfo();
	AvgInfo();
	
	return 0;

}
