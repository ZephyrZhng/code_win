/*
The first two consecutive numbers to have two distinct prime factors are:
14 = 2 x 7
15 = 3 x 5
The first three consecutive numbers to have three distinct prime factors are:
644 = 2^2 x 7 x 23
645 = 3 x 5 x 43
646 = 2 x 17 x 19.
Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers?
*/
//134043
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

bool prime(int x)
{
	if(x == 1) return false;
	for(int i = 2; i <= sqrt(x); ++i)
		if(!(x % i))
			return false;
	return true;
}

void display(vector<int>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
}

void fac(int x, vector<int>& v)
{
	if(prime(x))
	{
		printf("%d\t", x);
		v.push_back(x);
	}
	else
	{
		int i;
		for(i = 2; i <= sqrt(x); ++i)
			if(!(x % i))
			{
				printf("%d\t", i);
				v.push_back(i);
				break;
			}
		fac(x / i, v);
	}
}

bool _4DistinctPrimeFacs(int x)
{
	vector<int> v;
	v.clear();
	printf("\t");
	fac(x, v);
	printf("\t");
	for(int i = 0; i < v.size(); ++i)
		if(!(prime(v[i])))
		{
			printf("false\n");
			return false;
		}
	for(vector<int>::iterator i = v.begin(); i != v.end(); ++i)
		for(vector<int>::iterator j = i + 1; j != v.end(); )
			if(*i == *j)
				v.erase(j);
			else ++j;
	if(v.size() == 4)
	{
		printf("true\n");
		return true;
	}
	else
	{
		printf("false\n");
		return false;
	}
}

int main()
{	
	
	int cnt(0);
	for(int i = 1; ; ++i)
	{
		printf("%d\n", i);
		if(_4DistinctPrimeFacs(i))
		{
			++cnt;
			if(cnt == 4)
			{
				printf("%d\n", i - 3);
				break;
			}
		}
		else cnt = 0;
	}
	
	return 0;
}