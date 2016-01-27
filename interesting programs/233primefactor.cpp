#include <cstdio>
#include <cmath>
#include <limits>
using namespace std;

#define MAX numeric_limits<long long>::max()

bool isprime(long long n)
{
	for(long long i = 2; i <= sqrt(n); ++i)
	{
		if(!(n % i))
		{
			return false;
		}
	}
	return true;
}

void f(long long n)
{
	if(isprime(n) && n > 1)
	{
		printf("%lld\t", n);
	}
	else if(!isprime(n) && n > 3)
	{
		long long i;
		for(i = 2; i <= sqrt(n); ++i)
		{
			if(isprime(i) && !(n % i))
			{
				printf("%lld\t", i);
				break;
			}
		}
		long long next = n / i;
		f(next);
	}
}

int main()
{
	
	long long N;

	printf("%lld\n", MAX);

	for(N = 233; N <= MAX; N = N * 10 + 3)
	{
		printf("%lld:\t", N);
		f(N);
		printf("\n");
	}
	

	//test
	/*
	long long test;

	scanf("%lld", &test);
	if(test > MAX)
	{
		printf("Test is too big!\n");
	}
	else
	{
		if(!isprime(test))
		{
			f(test);
		}
		else
		{
			printf("Test is a prime!\n");
		}
		printf("\n");
	}
	*/
	/*
	int i;
	for( ; scanf("%d", &i) == 1; )
	{
		printf("%d\t", i);
		if(isprime(i))
		{
			printf("Yes!\n");
		}
		else
		{
			printf("No!\n");
		}
	}
	*/

	return 0;
}