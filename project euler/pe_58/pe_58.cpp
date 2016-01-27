#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
#include <windows.h>

using namespace std;

/*
Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.

37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right diagonal,
but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime;
that is, a ratio of 8/13 ~ 62%.

If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed.
If this process is continued, what is the side length of the square spiral
for which the ratio of primes along both diagonals first falls below 10%?
*/
// 26241

bool is_prime(int n)
{
	for(int i = 2; i <= sqrt(n); ++i)
	{
		if(!(n % i))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	double p     = 8.0 / 13.0;
	int prime    = 8;
	int diagonal = 13;
	int l        = 7;
	while(p > 0.1)
	{
		diagonal += 4;
		l        += 2;
		if(is_prime(l * l - 3 * l + 3)) ++prime;
		if(is_prime(l * l - 2 * l + 2)) ++prime;
		if(is_prime(l * l -     l + 1)) ++prime;
		p        = (double)prime / (double)diagonal;
		cout << l << " " << p << endl;
	}

	return 0;
}