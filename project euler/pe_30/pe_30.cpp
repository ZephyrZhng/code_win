/*
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 14 is not a sum it is not included.
The sum of these numbers is 1634 + 8208 + 9474 = 19316.
Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/
//443839
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int ans(0);
	for(int i = 10; i < 999999; ++i)
	{
		int sum(0);
		for(int n = i; n > 0; n /= 10)
		{
			sum += pow(n % 10, 5);
		}
		if(sum == i)
		{
			ans += sum;
			cout << sum << endl;
		}
	}
	cout << ans << endl;

	return 0;
}