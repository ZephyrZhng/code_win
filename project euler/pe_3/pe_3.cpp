/*
project euler problem 3
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143 ?
*/
//只能过样例
//
#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

const long long x = 600851475143;

bool judge_prime_num(long long a)
{
	long long i;

	if(a == 1)
	{
		return false;
	}
	for(i = 2; i <= a - 1; ++i)
	{
		if(!(a % i))
		{
			return false;
		}
	}
	return true;
}

int main()
{

	long long MAX = numeric_limits<long long>::max();
	cout << x << endl;
	cout << MAX << endl;

	if(judge_prime_num(x))
	{
		cout << "x is a prime number!" << endl;
	}
	else
	{
		cout << "x is not a prime number!" << endl;
	}

	long long i;

	for(i = x - 1; i > 1; --i)
	{
		if(!(x % i))
		{
			cout << i << endl;
			if(judge_prime_num(i))
			{
				break;
			}
		}
	}

	/*
	for(int i = 1; i <= 100; ++i)
	{
		if(judge_prime_num(i))
		{s
			cout << i << endl;
		}
	}
	*/

	return 0;
}
