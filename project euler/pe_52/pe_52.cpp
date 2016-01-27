/*
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, 
but in a different order.
Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/
//142857
#include <iostream>
#include <cstdio>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

void num2vector(long long x, vector<int>& v)
{
	for(long long a = x; x > 0; x /= 10)
	{
		v.push_back(x % 10);
	}
	reverse(v.begin(), v.end());
}

bool v1equaltov2(const vector<int>& v1, const vector<int>& v2)
{
	if(v1.size() != v2.size()) return false;
	for(int i = 0; i < v1.size(); ++i)
		if(v1[i] != v2[i]) return false;
	return true;
}

bool check(vector<int> vi, const vector<int>& vj)
{
	do
	{
		if(v1equaltov2(vi, vj)) return true;
	}while(next_permutation(vi.begin(), vi.begin() + vi.size()));
	return false;
}

int main()
{
	for(long long i = 1; ; ++i)
	{
		long long i2 = 2 * i;
		printf("%lld:\t%lld\t", i, i2);
		vector<int> v2;
		num2vector(i2, v2);
		bool flag(true);
		for(int j = 3; j <= 6; ++j)
		{
			long long ij = i * j;
			printf("%lld\t", ij);
			vector<int> vj;
			num2vector(ij, vj);
			if(!check(v2, vj)) flag = false;
		}
		if(flag)
		{
			printf("true\n%lld\n", i);
			break;
		}
		else printf("false\n");
	}

	return 0;
}