#include <stdio.h>


int change(char *a, char *b);

int main()
{
	char a[20] = "hi";
	char b[20] = "hello";
	printf("%s, %s\n", a, b);
	change(a, b);
	printf("%s, %s\n", a, b);
}


int change(char *a, char *b){
	char buf[20] = "hello";
	a = buf;
	b = "hi";
	return 0;
}
