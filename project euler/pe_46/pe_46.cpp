/*
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime 
and twice a square.
9 = 7 + 2x1^2
15 = 7 + 2x2^2
21 = 3 + 2x3^2
25 = 7 + 2x3^2
27 = 19 + 2x2^2
33 = 31 + 2x1^2
It turns out that the conjecture was false.
What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
*/
//5777
#include <iostream>
#include <cmath>
using namespace std;

const int lowerlimit = 33;

bool prime(int x)
{
	if(x == 1) return false;
	for(int i = 2; i <= sqrt(x); ++i)
		if(!(x % i))
			return false;
	return true;
}

inline bool check_square(int x){return sqrt(x) * sqrt(x) == x;}

bool check_conjecture(int x)
{
	for(int i = 2; i <= x - 2; ++i)
	{
		if(!prime(i) || (x - i) % 2) continue;
		if(check_square((x - i) / 2)) return true;
	}
	return false;
}

int main()
{
	for(int i = lowerlimit + 2; ; i += 2)
	{
		if(prime(i)) continue;
		if(!check_conjecture(i)) 
		{cout << i << endl; break;}
	}
	return 0;
}
