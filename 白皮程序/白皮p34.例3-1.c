#include<stdio.h>
#define len 1000
int a[len]={0};
int main()
{
	int i,j,n,k;
	int button(int x);
	scanf("%d %d",&n,&k);
	for(i=1;i<=k;i++)
	{
		for(j=0;j<n;j++)
		{
			if((j+1)%i==0)
			{
				a[j]=button(a[j]);
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(a[i])
		{
			printf("%d ",i+1);
		}
	}
	printf("\n");
	return 0;
}

int button(int x)
{
	if(x)
	{
		x=0;
	}
	else
	{
		x=1;
	}
	return x;
}
