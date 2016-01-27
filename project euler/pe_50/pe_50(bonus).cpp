/*
The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.
The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
Which prime, below one-million, can be written as the sum of the most consecutive primes?
*/
//
//在计算获得的文件中查找答案
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct elem
{
	int num;
	int cnt;
};

int main()
{
	ifstream infile("E:\\重要文档\\programs\\project_euler\\pe_50\\output.txt");
	if(!infile) printf("文件打开失败！\n");
	else
	{
		int i(0);
		vector<struct elem> v;
		for(int i = 0; infile.good(); ++i)
		{
			elem temp;
			infile >> temp.num >> temp.cnt;
			v.push_back(temp);
			printf("%d\t%d\n", v[i].num, v[i].cnt);
		}
		int m(0), pos(0);
		for(int i = 0; i < v.size(); ++i)
			if(v[i].cnt > m)
			{
				m = v[i].cnt;
				pos = i;
			}
		printf("\n%d\t%d\n", v[pos].num, v[pos].cnt);
		infile.close();
	}

	return 0;
}
