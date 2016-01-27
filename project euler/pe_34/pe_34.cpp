/*
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
Find the sum of all numbers which are equal to the sum of the factorial of their digits.
Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/
//40730
#include <iostream>
using namespace std;

int fac(int n)
{
	if(n == 0)
	{
		return 1;
	}
	else
	{
		return n * fac(n - 1);
	}
}

int main()
{
	int ans(0);
	for(int i = 10; i <= 9999999; ++i)
	{
		int sum(0);
		for(int x = i; x > 0; x /= 10)
		{
			sum += fac(x % 10);
		}
		if(sum == i)
		{
			ans += sum;
			cout << i << endl;
		}
	}
	cout << ans << endl;

	return 0;
}