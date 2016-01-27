#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

int				c    = 50;
int 			n    = 5;
vector<int>		my_w = { 0, 5,25,27,15,30};
vector<float> 	my_p = { 0,12,44,46,30,50};
vector<int> 	w(n + 1);
vector<float> 	p(n + 1);
int 			cw;
float 			cp;
float 			bestp;

template<typename t>
void disp(const vector<t>& v)
{
	for(auto& p: v)
		cout << p << " ";
	cout << endl;
}


float bound(int i)
{
	int 	cleft = c - cw;
	float 	b     = cp;
	while(i <= n && w[i] <= cleft)
	{
		cleft -= w[i];
		b     += p[i];
		++i;
	}
	if(i <= n)
	{
		b += p[i] * cleft / w[i];
	}

	return b;
}


void backtrack(int i)
{
	if(i > n)
	{
		bestp = cp;
		return;
	}
	if(cw + w[i] <= c)
	{
		cw += w[i];
		cp += p[i];
		backtrack(i + 1);
		cw -= w[i];
		cp -= p[i];
	}
	if(bound(i + 1) > bestp)
	{
		backtrack(i + 1);
	}
}


typedef struct object
{
	int 	id;
	float	d;
}object;

float knapsack()
{
	// int		big_w = 0;
	// float	big_p = 0;
	vector<object> q(n);
	for(int i = 1; i <= n; ++i)
	{
		q[i - 1].id = i;
		q[i - 1].d  = 1.0 * my_p[i] / my_w[i];
		// big_p      += my_p[i];
		// big_w      += my_w[i];
	}
	/*if(big_w <= c)
		return big_p;*/

	for(int i = 0; i < q.size(); ++i)
		for(int j = i + 1; j < q.size(); ++j)
			if(q[j].d < q[i].d)
				swap(q[i], q[j]);

	for(int i = 1; i <= n; ++i)
	{
		p[i] = my_p[q[i - 1].id];
		w[i] = my_w[q[i - 1].id];
	}

	cout << "c: " << c << endl;
	cout << "n: " << n << endl;
	cout << "p:"  << endl;
	disp(p);
	cout << "w:"  << endl;
	disp(w);

	cp    = 0;
	cw    = 0;
	bestp = 0;

	backtrack(1);
	return bestp;
}

int main()
{
	cout << knapsack() << endl;
	return 0;
}