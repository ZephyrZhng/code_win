/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. 
For example, 2143 is a 4-digit pandigital and is also prime.
What is the largest n-digit pandigital prime that exists?
*/
//7652413
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cmath>
using namespace std;

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

int main()
{
	int ans(0);
	for(int i = 1; i <= 9; ++i)
	{
		vector<int> v;
		for(int j = 1; j <= i; ++j)
		{
			v.push_back(j);
		}
		do
		{
			int temp = vector2int(v);
			if(prime(temp))
			{
				cout << temp << endl;
				ans = temp > ans? temp: ans;
			}
		}while(next_permutation(v.begin(), v.begin() + v.size()));
		cout << ans << endl;	
	}

	return 0;
}