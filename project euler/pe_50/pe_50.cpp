/*
The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.
The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
Which prime, below one-million, can be written as the sum of the most consecutive primes?
*/
//
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

const int upperlimit = 1000000;
const int start = 133993;

struct elem
{
	int num;
	int cnt;
};

bool prime(int x)
{
	if(x == 1) return false;
	for(int i = 2; i <= sqrt(x); ++i)
		if(!(x % i))
			return false;
	return true;
}

int next_prime(int x)
{
	for(int ans = x + 1; ; ++ans)
		if(prime(ans)) return ans;
}

struct elem prime_fac(int x)
{
	int i(2);
	for(; i < x; i = next_prime(i))
	{
		int sum(0), cnt(0);
		for(int j = i; sum < x; j = next_prime(j))
		{
			sum += j;
			if(sum < x) ++cnt;
			if(sum == x)
			{
				++cnt;
				elem return_value = {x, cnt};
				return return_value;
			}
			if(sum > x) break;
		}
	}
	elem return_value = {x, 0};
	return return_value;
}

int main()
{
	ofstream of("E:\\重要文档\\programs\\project_euler\\pe_50\\output.txt");
	if(!of) printf("文件打开失败！\n");
	else
	{
		of << endl;
		vector<struct elem> v;
		for(int i = next_prime(start); i < upperlimit; i = next_prime(i))
		{
			elem temp = prime_fac(i);
			v.push_back(temp);
			printf("%d\t%d\n", temp.num, temp.cnt);
			of << temp.num << "\t" << temp.cnt << endl;
		}
		of.close();
	}

	return 0;
}