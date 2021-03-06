/*
project euler problem 21
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a != b, 
then a and b are an amicable pair and each of a and b are called amicable numbers.
For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. 
The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
Evaluate the sum of all the amicable numbers under 10000.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int Max = 10000;

int d(int n)
{
	int i, s;

	for(i = 1, s = 0; i < n; ++i)
	{
		if(!(n % i))
		{
			s += i;
		}
	}

	return s;
}

int main()
{
	int v[Max];
	int i, j;
	long long sum(0);
	for(i = 0; i < Max; ++i)
	{
		v[i] = d(i + 1);
		cout << i + 1 << " " << v[i] << endl;
	}
	cout << v[283] << endl << v[219] << endl;

	for(i = 0; i < Max; ++i)
	{
		for(j = i + 1; j < Max; ++j)
		{
			if((j + 1 == v[i]) && (v[j] == i + 1))
			{
				sum = sum + i + j + 2;
				break;
			}
		}
	}
	cout << sum << endl;
}