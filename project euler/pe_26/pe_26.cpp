/*
A unit fraction contains 1 in the numerator. 
The decimal representation of the unit fractions with denominators 2 to 10 are given:
1/2 =  0.5 
1/3 =  0.(3) 
1/4 =  0.25 
1/5 =  0.2 
1/6 =  0.1(6) 
1/7 =  0.(142857) 
1/8 =  0.125 
1/9 =  0.(1) 
1/10 =  0.1 
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. 
It can be seen that 1/7 has a 6-digit recurring cycle.
Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/
//983
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int upperlimit = 1000;

struct elem
{
	int quotient;
	int remainder;
};

long long FindRepetend(int i)
{
	int x(10);
	long long RepetendLen;


	vector<struct elem> v;

	for(;;)
	{
		elem temp;
		temp.quotient = int(x / i);
		temp.remainder = x % i;
		v.push_back(temp);
		if(temp.remainder == 0)
		{
			RepetendLen = 0;
			break;
		}
		x = temp.remainder * 10;

		int pos(0);
		bool flag(false);
		for(; pos < v.size() - 1; ++pos)
		{
			if(v[pos].remainder == temp.remainder)
			{
				flag = true;
				break;
			}
		}
		if(flag)
		{
			RepetendLen = v.size() - pos - 1;
			break;
		}
	}

	return RepetendLen;
}

int main()
{
	long long MAXLEN(0);
	int MAX(2);

	for(int i = 2; i < upperlimit; ++i)
	{
		long long temp = FindRepetend(i);
		if(temp > MAXLEN)
		{
			MAX = i;
			MAXLEN = temp;
		}
		cout << "1/" << i << ": " << temp << endl;
	}
	cout << endl << "1/" << MAX << ": " << MAXLEN << endl;

	return 0;
}