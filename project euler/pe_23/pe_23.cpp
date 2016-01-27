/*
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, 
which means that 28 is a perfect number.
A number n is called deficient if the sum of its proper divisors is less than n 
and it is called abundant if this sum exceeds n.
As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, 
the smallest number that can be written as the sum of two abundant numbers is 24. 
By mathematical analysis, it can be shown that all integers greater than 28123 
can be written as the sum of two abundant numbers. 
However, this upper limit cannot be reduced any further by analysis 
even though it is known that the greatest number that cannot be expressed 
as the sum of two abundant numbers is less than this limit.
Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/
//4179871
#include <cstdio>
#include <cstring>
using namespace std;

#define limit 28123

bool abundant(int n)
{
	if(n == 1)
	{
		return false;
	}

	int sum(0);
	for(int i = 1; i < n; ++i)
	{
		if(!(n % i))
		{
			sum += i;
		}
	}
	if(sum > n)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool judge(int n)
{
	for(int i = 1; i <= n / 2; ++i)
	{
		if(abundant(i) && abundant(n - i))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	/*
	printf("Judge 1 abundant?(expected to be false): ");
	if(abundant(1))
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");
	}
	printf("Judge 1?(expected to be true): ");
	if(judge(1))
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");
	}
	printf("Judge 12 abundant?(expected to be yes): ");
	if(abundant(12))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
	printf("Judge 24?(expected to be false): ");
	if(judge(24))
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");
	}
	*/
	
	long long sum(0);
	
	for(int i = 1; i < limit; ++i)
	{
		if(judge(i))
		{
			printf("%d\n", i);
			sum += i;
		}
	}
	printf("%lld\n", sum);
	

	return 0;
}