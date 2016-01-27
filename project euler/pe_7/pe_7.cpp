/*
project euler problem 7
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, 
we can see that the 6th prime is 13.
What is the 10001st prime number?
*/
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int n = 10001;
int arr[n];

bool judge_prime(int x)
{
	int i;
	int flag;

	for(i = 2, flag = 1; i <= sqrt(x); ++i)
	{
		if(!(x % i))
		{
			flag = 0;
			break;
		}
	}
	if(flag)
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
	int x;
	int cnt;

	memset(arr, 0, sizeof(arr));
	for(x = 2, cnt = 0; cnt < n; ++x)
	{
		if(judge_prime(x))
		{
			arr[cnt] = x;
			if(cnt == n - 1)
			{
				cout << arr[cnt] << endl;
				break;
			}
			++cnt;
		}
	}

	return 0;
}