/*
The number, 197, is called a circular prime because all rotations of the digits: 
197, 971, and 719, are themselves prime.
There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
How many circular primes are there below one million?
*/
//55
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
using namespace std;

const int upperlimit = 1000000;

bool prime(int x)
{
	if(x == 1)
	{
		return false;
	}
	for(int i = 2; i <= sqrt(x); ++i)
	{
		if(!(x % i))
		{
			return false;
		}
	}
	return true;
}

void int2vector(int a, vector<int>& v)
{
	for(int x = a; x > 0; x /= 10)
	{
		v.push_back(x % 10);
	}
	reverse(v.begin(), v.end());
}

int vector2int(const vector<int>& v)
{
	int ans(0);
	for(int i = 0; i < v.size(); ++i)
	{
		ans *= 10;
		ans += v[i];
	}
	return ans;
}

bool circulate(int a, vector<int>& va)
{

	for(int i = 0; i < va.size() - 1; ++i)
	{
		int bottom = va[0];
		vector<int>::iterator it = va.begin();
		va.erase(it);
		va.push_back(bottom);
		if(!prime(vector2int(va)))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int sum(0);
	for(int i = 2; i < upperlimit; ++i)
	{
		vector<int> v;
		int2vector(i, v);
		if(find(v.begin(), v.end(), 0) != v.end())
		{
			continue;
		}
		if(prime(i) && circulate(i, v))
		{
			++sum;
			cout << i << endl;
		}
	}
	cout << sum << endl;

	return 0;
}