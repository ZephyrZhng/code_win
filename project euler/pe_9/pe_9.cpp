/*
project euler problem 9
A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,
a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/
#include <iostream>
using namespace std;

const int n = 1000;

bool judge(int x, int y, int z)
{
	if(x * x + y * y == z * z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool judge_PTri(int i, int j, int k)
{
	if(judge(i, j, k) || judge(i, k, j) || judge(j, i, k) ||
		judge(j, k, i) || judge(k, i, j) || judge(k, j, i))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	int i, j, flag(0);

	for(i = 1; i <= n - 2; ++i)
	{
		for(j = 1; j <= n - i - 1; ++j)
		{
			if(judge_PTri(i, j, n - i - j))
			{
				flag = 1;
				cout << i * j * (n - i - j) << endl;
				goto end;
			}
		}
	}

	end:
	if(!flag)
	{
		cout << "shit" << endl;
	}
	return 0;
}