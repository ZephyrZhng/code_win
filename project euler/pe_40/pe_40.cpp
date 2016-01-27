/*
An irrational decimal fraction is created by concatenating the positive integers:
0.123456789101112131415161718192021...
It can be seen that the 12th digit of the fractional part is 1.
If dn represents the nth digit of the fractional part, find the value of the following expression.
d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000
*/
//210
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

const int upperlimit = 1000000;

void int2vector(int a, vector<int>& v)
{
	v.clear();
	for(int x = a; x > 0; x /= 10)
	{
		v.push_back(x % 10);
	}
	reverse(v.begin(), v.end());
}

int main()
{
	vector<int> v;
	for(int i = 1; v.size() < upperlimit; ++i)
	{
		vector<int> vi;
		int2vector(i, vi);
		v.insert(v.end(), vi.begin(), vi.end());
	}
	int ans(1);
	for(int i = 1; i < upperlimit; i *= 10)
	{
		ans *= v[i - 1];
		cout << i << ": " << v[i - 1] << endl;
	}
	cout << ans << endl;
}