#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

void display(const vector<int>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << "\t";
	cout << endl;
}

void display(const vector< vector<int> >& v)
{
	for(int i = 0; i < v.size(); ++i)
		display(v[i]);
}

void find_saddle_point(vector< vector<int> > v, vector<int>& ans)
{
	for(int i = 0; i < v.size(); ++i)
	{
		vector<int>::iterator it = min_element(v[i].begin(), v[i].end());
		int temp = *it;
		int pos = it - v[i].begin();
		bool flag(true);
		for(int ii = 0; ii < v.size(); ++ii)
		{
			if(ii == i) continue;
			if(v[ii][pos] > temp)
			{
				flag = false;
				break;
			}
		}
		if(flag) ans.push_back(temp);
	}
}

int main()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\题\\马鞍点.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}
	int x, y;
	input >> x >> y;
	cout << x << "\t" << y << endl;
	vector< vector<int> > v;
	for(int i = 0; i < x; ++i)
	{
		vector<int> vi;
		v.push_back(vi);
		for(int j = 0; j < y; ++j)
		{
			int temp;
			input >> temp;
			v[i].push_back(temp);
		}
	}
	input.close();
	display(v);

	vector<int> ans;
	find_saddle_point(v, ans);
	display(ans);

	return 0;
}