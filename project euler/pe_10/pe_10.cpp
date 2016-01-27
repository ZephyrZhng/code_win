/*
project euler problem 10
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
Find the sum of all the primes below two million.
*/
#include <iostream>
#include <cmath>
using namespace std;

const int n = 2000000;

bool judge_prime(int x)
{
	int i;
	int flag;

	for(i = 2, flag = 1; i <= sqrt(x); ++i)
	{
		if(!(x % i))
		{
			flag = 0;
			break;
		}
	}
	if(flag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	int i;
	long long sum;

	for(i = 2, sum = 0; i < n; ++i)
	{
		if(judge_prime(i))
		{
			sum += i;
		}
	}
	cout << sum << endl;

	return 0;
}