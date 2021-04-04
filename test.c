#include <stdio.h>


int main(){

	char a = 'a';
	printf("%c", a);
	*a = 97;
	printf("%c", a);
	return 0;
}
