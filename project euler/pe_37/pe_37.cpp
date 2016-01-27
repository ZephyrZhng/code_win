/*
The number 3797 has an interesting property. Being prime itself, 
it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. 
Similarly we can work from right to left: 3797, 379, 37, and 3.
Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/
//748317
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
using namespace std;

bool prime(long long x)
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
	v.clear();
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

bool truncatablel2r(vector<int>& v)
{
	int len = v.size();
	for(int i = 0; i < len; ++i)
	{
		v.erase(v.begin());
		if(!prime(vector2int(v)))
		{
			return false;
		}
	}
	return true;
}

bool truncatabler2l(vector<int>& v)
{
	int len = v.size();
	for(int i = 0; i < len; ++i)
	{
		v.erase(v.end() - 1);
		if(!prime(vector2int(v)))
		{
			return false;
		}
	}
	return true;
}

int main()
{	
	int cnt(0), sum(0);

	for(int i = 10; cnt < 11; ++i)
	{
		vector<int> v;
		int2vector(i, v);
		if(prime(i) && truncatablel2r(v) && v[0] != 1 && v[v.size() - 1] != 1)
		{
			int2vector(i, v);
			if(truncatabler2l(v))
			{
				++cnt;
				sum += i;
				cout << i << endl;
			}
		}
	}
	cout << sum << endl;
	
	return 0;
}
