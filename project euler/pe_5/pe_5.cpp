/*
project euler problem 5
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
#include <iostream>
using namespace std;

bool judge(int x)
{
	int i, flag;

	for(i = 1, flag = true; i <= 20; ++i)
	{
		if(x % i)
		{
			flag = false;
			break;
		}
	}

	return flag;
}

int main()
{
	int i;

	for(i = 1; !judge(i); ++i);
	cout << i << endl;
	
	return 0;
}