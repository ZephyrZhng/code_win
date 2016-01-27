#include <stdio.h>
#include <string.h>
#define n 4
int main ()
{
	int i,j,matrix[n][n];
	for(i=0;i<n*n;i++)
	{
		scanf("%d",&matrix[i]);
	}
	for(i=0;i<n*n;i++)
	{
		printf("%d",matrix[i]);
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",matrix[i][n-1-j]);
		}
		printf("\n");
	}
	return 0;
}
