#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1024 

 
int calculate(int p[], int n)
{   
    int m[n][n];
    int i, j, k, L, q;
 
    for (i=1; i<n; i++)
        m[i][i] = 0;    //number of multiplications are 0(zero) when there is only one matrix
 
    //Here L is chain length. It varies from length 2 to length n.
    for (L=2; L<n; L++)
    {
        for (i=1; i<n-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INT_MAX;  //assigning to maximum value
 
            for (k=i; k<=j-1; k++)
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;    //if number of multiplications found less that number will be updated.
                }
            }
        }
    }
 
    return m[1][n-1];   //returning the final answer which is M[1][n]
 
}
 
int main()
{
//    int n,i;
 //   printf("Enter number of matrices\n");
 // scanf("%d",&n);
 
 //   n++;
	FILE *fp = fopen("MCMproblem.txt", "r");

	while(!feof(fp)){
        int i = 0; 
        int j = 0;
		int *num[MAX];
        char ex[MAX];
        char *array[MAX];
        fgets(ex, MAX, fp);
        char *ptr = strtok(ex, " ");
        
        while(ptr != NULL){
            array[j] = ptr;
            num[j] = atoi(ptr);
            ptr = strtok(NULL, " ");
            j++;
        }
		int arrsize  = sizeof(num)/sizeof(num[0]);
		printf("Calculation%d Result:%d\n", i+1, calculate(num, arrsize));
		i++;
	}
    /*int arr[n];dd
 
    printf("Enter dimensions \n");
 
    for(i=0;i<n;i++)
    {
        printf("Enter d%d :: ",i);
        scanf("%d",&arr[i]);
    }
 
    int size = sizeof(arr)/sizeof(arr[0]);
 
    printf("Minimum number of multiplications is %d ", calculate(arr, size));
 */
    return 0;
}
