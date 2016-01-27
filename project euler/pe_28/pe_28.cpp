/*
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13
It can be verified that the sum of the numbers on the diagonals is 101.
What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/
//669171001
#include <iostream>
#include <vector>
using namespace std;

const int upperlimit = 1001;

int f(int n)
{
	if(n == 1)
	{
		return 1;
	}
	return f(n - 1) + 8 * n - 14;
}

int main()
{
	vector<int> v;
	for(int i = 1; i <= (upperlimit - 1) / 2 + 1; ++i)
	{
		v.push_back(f(i));
		cout << i << ": " << v[i - 1] << endl;
	}
	long long sum(1);
	for(int i = 1; i < v.size(); ++i)
	{
		v[i] = 4 * v[i] + 12 * i;
		sum += v[i];
	}
	cout << sum << endl;

	return 0;
}