#include<stdio.h>
#define len 100
int array[len][len]={0};
int main()
{
	int  n,i,j,k,num=1;
	scanf("%d",&n);
	for(i=0,j=n-1;i<n/2;i++,j--)
	{
		for(k=i;k<n-i;k++,num++)
		{
			array[k][j]=num;
		}
		for(k=j-1;k>=n-j-1;k--,num++)
		{
			array[n-i-1][k]=num;
		}
		for(k=n-i-2;k>=i;k--,num++)
		{
			array[k][n-j-1]=num;
		}
		for(k=n-j;k<j;k++,num++)
		{
			array[i][k]=num;
		}
	}
	if(n%2)
	{
		array[(n-1)/2][(n-1)/2]=num;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",array[i][j]);
		}
		printf("\n");
	}
	return 0;
}
