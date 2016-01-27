#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

#define eps 1e-6

long double my_sqrt1(long double a, long double p)
{
	if(fabs(p * p - a) < eps) return p;
	else return my_sqrt1(a, (p + a / p) / 2);
}

long double my_sqrt2(long double a)
{
	long double p;
	for(p = 1; fabs(p * p - a) >= eps; )
		p = (p + a / p) / 2;
	return p;
}

int main()
{
	cout << my_sqrt1(2, 1) << endl << my_sqrt2(2) << endl;

	return 0;
}