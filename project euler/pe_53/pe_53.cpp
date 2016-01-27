/*
There are exactly ten ways of selecting three from five, 12345:
123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
In combinatorics, we use the notation, 5C3 = 10.
In general,
nCr =  n!/r!(nr)! ,where r  n, n! = n(n1)...321, and 0! = 1.
It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
How many, not necessarily distinct, values of  nCr, for 1 <= n <= 100, are greater than one-million?
*/
//运行太慢！
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

const int upperlimit = 1000000;

long long C(int n, int r)
{
	if(n == r || r == 0) return 1;
	if(r == 1) return n;
	return C(n - 1, r) + C(n - 1, r - 1);
}

int main()
{
	
	long long cnt(0);
	for(int n = 1; n <= 100; ++n)
		for(int r = 0; r <= int(n / 2); ++r)
		{
			long long c = C(n, r);
			if(c > upperlimit)
			{
				++cnt;
				cout << cnt << "\t" << n << "C" << r << " = " << c << endl;
			}
		}
	cout << cnt << endl;	

	return 0;
}