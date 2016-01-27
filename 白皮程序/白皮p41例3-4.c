#include <stdio.h>
#include <string.h>
char s[5005],_s[5005];
int main ()
{
	int i,j,left,right,flag;
	for(i=0;s[i-1]!='\n';i++)
	{
		scanf("%c",&s[i]);
	}
	for(flag=1,i=0;i<strlen(s);i++)
	{
		strcpy(_s,strlwr(s));
		for(left=0,right=0;i-left>=0 && i+right<strlen(_s);)
		{
			for(;!(_s[i+right]>='a' && _s[i+right]<='z');right++);
			for(;!(_s[i+left]>='a' && _s[i+left]<='z');left++);
			if(_s[i+right]!=_s[i-left])
			{
				flag=0;
				goto outer;
			}
			else
			{
				continue;
			}
		}
	}
	outer:if(flag)
	{
		for(j=i-left;j<=i+right;j++)
		{
			printf("%c",s[j]);
		}
	}
	return 0;
}
