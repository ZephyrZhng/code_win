/*
Euler discovered the remarkable quadratic formula:
n^2 + n + 41
It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. 
However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, 
and certainly when n = 41, 41^2 + 41 + 41 is clearly divisible by 41.
The incredible formula  n^2 - 79n + 1601 was discovered, 
which produces 80 primes for the consecutive values n = 0 to 79. 
The product of the coefficients, 79 and 1601, is 126479.
Considering quadratics of the form:
n^2 + an + b, where |a| < 1000 and |b| < 1000
where |n| is the modulus/absolute value of n
e.g. |11| = 11 and |-4| = 4
Find the product of the coefficients, a and b, 
for the quadratic expression that produces the maximum number of primes for consecutive values of n, 
starting with n = 0.
*/
//-59231
#include <iostream>
using namespace std;

const int upperlimit = 1000;

bool prime(long long x)
{
	if(x <= 1)
	{
		return false;
	}
	for(long long i = 2; i < x; ++i)
	{
		if(!(x % i))
		{
			return false;
		}
	}
	return true;
}

inline long long f(int n, int a, int b)
{
	return n * n + a * n + b;
}

int check(int a, int b)
{
	int n;
	for(n = 0; ; ++n)
	{
		if(!prime(f(n, a, b)))
		{
			break;
		}
	}
	return n;
}

int main()
{
	int a, b, m(0), maxa(0), maxb(0);
	for(a = -upperlimit + 1; a < upperlimit; ++a)
	{
		for(b = -upperlimit; b < upperlimit; ++b)
		{
			int n = check(a, b);
			cout << a << " " << b << " " << n << endl;
			if(n > m)
			{
				m = n;
				maxa = a;
				maxb = b;
			}
		}
	}
	cout << "a: " << maxa << " " << "b: " << maxb << " " << m << endl;
	cout << "a * b: " << maxa * maxb << endl;

	return 0;
}