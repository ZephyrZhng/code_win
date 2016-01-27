#include<stdio.h>
int main()
{
	int check(int x,int y,int z);
	int i,j,k;
	for(i=100;i<=999;i++)
	{
		for(j=100;j<=999;j++)
		{
			for(k=100;k<=999;k++)
			{
				if(check(i,j,k) && j/i==2 && k/i==3)
				{
					printf("%d %d %d\n",i,j,k);
				}
			}
		}
	}
	return 0;
}

int check(int x,int y,int z)
{
	int i,j,k,l,m,flag=1,array[10]={0};
	for(i=0;i<=2;i++)
	{
		array[i]=x%10;
		x/=10;
	}
	for(j=3;j<=5;j++)
	{
		array[j]=y%10;
		y/=10;
	}
	for(k=6;k<=8;k++)
	{
		array[k]=z%10;
		z/=10;
	}
	for(l=0;l<=8;l++)
	{
		if(array[l]==0)
		{
			flag=0;
			goto end;
		}
		else
		{
			for(m=0;m<l;m++)
			{
				if(array[l]==array[m])
				{
					flag=0;
					goto end;
				}
			}
		}
	}
	end:return flag;
}
