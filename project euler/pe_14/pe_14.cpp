/*
project euler problem 14
The following iterative sequence is defined for the set of positive integers:
n -> n/2 (n is even)
n -> 3n + 1 (n is odd)
Using the rule above and starting with 13, we generate the following sequence:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. 
Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
Which starting number, under one million, produces the longest chain?
NOTE: Once the chain starts the terms are allowed to go above one million.
*/
#include <iostream>
using namespace std;

const int Max = 1000000;

long long CalChain(int StartingNum)
{
	long long chain(1);
	long long x;

	for(x = StartingNum; x != 1; ++chain)
	{
		if(x % 2)
		{
			x = 3 * x + 1;
		}
		else
		{
			x /= 2;
		}
	}

	return chain;
}

int main()
{
	int i, num(1);
	long long MaxChain;

	for(i = 1, MaxChain = 1; i < Max; ++i)
	{
		cout << i << " " << CalChain(i) << endl;
		if(CalChain(i) > MaxChain)
		{
			num = i;
			MaxChain = CalChain(i);
		}
	}
	cout << "num = " << num << endl;
	cout << "MaxChain = " <<  MaxChain << endl;

	return 0;
}