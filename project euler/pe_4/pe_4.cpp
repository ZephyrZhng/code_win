/*
project euler problen 4
A palindromic number reads the same both ways. 
The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 * 99.
Find the largest palindrome made from the product of two 3-digit numbers.
*/
#include <iostream>

using namespace std;

const int begin = 999;
const int end = 100;

int reverse(int x)
{
	int _x;

	for(_x = 0 ; x > 0; x /= 10)
	{
		_x *= 10;
		_x += x % 10;
	}

	return _x;
}

int main()
{
	int i, j, factor_1, factor_2, max(0);

	for(i = begin; i >= end; --i)
	{
		for(j = begin; j >= end; --j)
		{
			if(((i * j) == reverse(i * j)) && ((i * j) >= max))
			{
				factor_1 = i;
				factor_2 = j;
				max = i * j;
			}
		}
	}
	cout << factor_1 << " " << factor_2 << " " << max << endl;
	
	return 0;
}
