#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1024 

int s[MAX][MAX]; 

void ParseCommand(char *command, int *argc , char *argv[]){

	*argc = 0;
	int i=0;
	char *ptr = strtok(command, " ");	
	while(ptr != NULL){
		argv[i] = ptr;
		ptr = strtok(NULL, " ");
		i++;
		*argc+=1;
	}
}

void parens(int i, int j){
	if(i == j) {printf("A%d", i);}
	else {
		printf("(");
		parens(i, s[i][j]);
		parens(s[i][j]+1, j);
		printf(")");
	}
}

int calculate(int arr[], int size)
{
	int m[size][size];
	int i, j, k, r, q;
	 
    for (i=1; i<size; i++)
        m[i][i] = 0;    //number of multiplications are 0(zero) when there is only one matrix
 
    //Here L is chain length. It varies from length 2 to length n.
    for (r=2; r<size; r++)
    {
        for (i=1; i<size-r+1; i++)
        {
            j = i+r-1;
            m[i][j] = INT_MAX;  //assigning to maximum value
            for (k=i; k<j; k++)
            {
                q = m[i][k] + m[k+1][j] + arr[i-1]*arr[k]*arr[j];
                if (q < m[i][j])
                {
			m[i][j] = q;    //if number of multiplications found less that number will be updated.
			s[i][j] = k;
                }

            }

        }
    }
	printf("\nMinimum parenthesization:");
 		parens(i-1,j);
	printf("\n");
    return  m[1][size-1];   //returning the final answer which is M[1][n]
 
}
 
int main()
{
	FILE *fp = fopen("MCMproblem.txt", "r");	
	char str[MAX];
	int pnum = 1;

	while(fgets(str, MAX, fp) != NULL){
		int num[MAX];
		int count = 0;
		char *strnum[MAX] = {NULL};
		
		ParseCommand(str, &count, strnum);
		
		printf("Problem %d: ", pnum);
		
		for(int j=0; j<count; j++){
			num[j] = atoi(strnum[j]);
			printf("%d ", num[j]);
		}
		
		printf("The Minimum Result:%d, k = %d\n\n",  calculate(num,count), s[1][count]);
		pnum++;
	}
    return 0;
}

