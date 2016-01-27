//列主元Gauss消去法
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

void input(vector< vector<long double> >& v)
{
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i)
	{	
		vector<long double> vi;
		v.push_back(vi);
		for(int j = 0; j < n + 1; ++j)
		{
			long double vij;
			cin >> vij;
			v[i].push_back(vij);
		}
	}
}

void outputv(const vector<long double>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << "\t";
	cout << endl;
}

void output(const vector< vector<long double> >& v)
{
	for(int i = 0; i < v.size(); ++i)
		outputv(v[i]);
}

int search_max_abs(int i, int j, vector< vector<long double> >& v)
{
	int posi(i), ij;
	long double m(fabs(v[i][j]));
	for(ij = i + 1; ij < v.size(); ++ij)
		if(fabs(v[ij][j]) > m)
		{
			m = fabs(v[ij][j]);
			posi = ij;
		}
	return posi;
}

void swap(long double& a, long double& b)
{
	if(a == b) return;
	long double temp = a;
	a = b;
	b = temp;
}

void swapi1i2(int i1, int i2, int j, vector< vector<long double> >& v)
{
	//if(i1 == i2) return;
	for(int ij = j; ij < v.size() + 1; ++ij)
		swap(v[i1][ij], v[i2][ij]);
}

void set0(int i, int j, vector< vector<long double> >& v)
{
	for(int ij = i + 1; ij < v.size(); ++ij)
		v[ij][j] = 0;
}


void vi2minusvi1(int i1, int i2, int j, vector< vector<long double> >& v)
{
	long double fac = v[i2][j] / v[i1][j];
	for(int ij = j + 1; ij < v.size() + 1; ++ij)
		v[i2][ij] -= fac * v[i1][ij];
}

void subeliminate(int i, int j, vector< vector<long double> >& v)
{
	for(int ij = i + 1; ij < v.size(); ++ij)
		vi2minusvi1(i, ij, j, v);
}

void eliminate(vector< vector<long double> >& v)
{
	for(int i = 0; i < v.size() - 1; ++i)
	{
		int i_max_abs = search_max_abs(i, i, v);
		swapi1i2(i, i_max_abs, i, v);
		subeliminate(i, i, v);
		set0(i, i, v);
		output(v);
		cout << endl;
	}
}

void back_substitute(vector<long double>& ans, vector< vector<long double> >& v)
{
	for(int i = v.size() - 1; i >= 0; --i)
		if(i == v.size() - 1)
			ans.push_back(v[i][v.size()] / v[i][v.size() - 1]);
		else
		{
			int ansi(0);
			for(int j = v.size() - 1; j >= i + 1; --j, ++ansi)
				v[i][v.size()] -= v[i][j] * ans[ansi];
			ans.push_back(v[i][v.size()] / v[i][i]);
		}
}

int main()
{
	
	vector< vector<long double> > v;
	vector<long double> ans;
	ifstream data("E:\\重要文档\\programs\\数值分析\\列主元gauss消去法\\gauss data.txt");
	if(!data) cerr << "文件打开失败！" << endl;
	else 
	{
		int n;
		data >> n;
		cout << n << endl;
		for(int i = 0; i < n; ++i)
		{	
			vector<long double> vi;
			v.push_back(vi);
			for(int j = 0; j < n + 1; ++j)
			{
				long double vij;
				data >> vij;
				v[i].push_back(vij);
			}
		}
		data.close();
	}
	
	//input(v);

	cout << endl;
	output(v);
	cout << endl;
	
	eliminate(v);
	back_substitute(ans, v);
	reverse(ans.begin(), ans.end());
	outputv(ans);

	return 0;
}