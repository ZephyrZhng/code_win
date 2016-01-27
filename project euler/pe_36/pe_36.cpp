/*
The decimal number, 585 = 1001001001(2) (binary), is palindromic in both bases.
Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
(Please note that the palindromic number, in either base, may not include leading zeros.)
*/
//872187
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

const int upperlimit = 1000000;

void dec2bi(int x, vector<int>& v)
{
	for(int a = x; a > 0; a /= 2)
	{
		v.push_back(a % 2);
	}
	reverse(v.begin(), v.end());
}

void int2vector(int x, vector<int>& v)
{
	for(int a = x; x > 0; x /= 10)
	{
		v.push_back(x % 10);
	}
	reverse(v.begin(), v.end());
}

bool palindromic(const vector<int>& v)
{
	for(int i = 0; i < v.size() / 2; ++i)
	{
		if(v[i] != v[v.size() - i - 1])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int sum(0);
	for(int i = 0; i < upperlimit; ++i)
	{
		vector<int> vdec;
		int2vector(i, vdec);
		if(!(i % 10) || vdec[vdec.size() - 1] == 0)
		{
			continue;
		}
		vector<int> vbi;
		dec2bi(i, vbi);
		if(palindromic(vdec) && palindromic(vbi))
		{
			sum += i;
			cout << i << endl;
		}
	}
	cout << sum << endl;

	return 0;
}

