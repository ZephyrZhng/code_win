#include <stdio.h>
#include <string.h>
int main ()
{
	int i,j,a,b,mark,flag,_flag,count,digit[10];
	char given[15],num[20];
	for(i=0;given[i-1]!='\n';i++)
	{
		scanf("%c",&given[i]);
	}

	count=0;
	for(i=100;i<=999;i++)
	{
		for(memset(num,'\0',sizeof(num)),j=10;j<=99;j++)
		{
			digit[0]=i;
			digit[1]=j;
			digit[2]=(j%10)*i;
			digit[3]=(j/10)*i;
			digit[4]=i*j;
			b=0;
			for(a=0;a<=4;a++)
			{
				for(;digit[a]>0;digit[a]/=10,b++)
				{
					mark=digit[a]%10;
					switch(mark)
					{
						case 0:num[b]='0';break;
						case 1:num[b]='1';break;
						case 2:num[b]='2';break;
						case 3:num[b]='3';break;
						case 4:num[b]='4';break;
						case 5:num[b]='5';break;
						case 6:num[b]='6';break;
						case 7:num[b]='7';break;
						case 8:num[b]='8';break;
						case 9:num[b]='9';break;
					}
				}
			}
			flag=1;
			for(b=0;num[b]!='\0';b++)
			{
				_flag=0;
				for(a=0;given[a]!='\0';a++)
				{
					if(given[a]==num[b])
					{
						_flag=1;
						break;
					}
				}
				if(!_flag)
				{
					flag=0;
					break;
				}
			}
			if(flag)
			{
				count++;
				printf("<%d>\n  %d\nX  %d\n-----\n %d\n%d \n-----\n%d\n\n",count,i,j,(j%10)*i,(j/10)*i,i*j);
			}
		}
	}
	printf("\nThe number of solution=%d",count);
	return 0;
}
