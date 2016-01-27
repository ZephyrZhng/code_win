//GS
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

const int ITNUM = 100;

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

void pretreat(vector< vector<long double> >& A, vector<long double>& b)
{
	for(int i = 0; i < A.size(); ++i)
		if(!A[i][i])
			for(int ii = i + 1; ii < A.size(); ++ii)
				if(A[ii][ii])
				{
					swap(A[i], A[ii]);
					swap(b[i], b[ii]);
				}
}

void B(vector< vector<long double> >& A, const vector<long double>& b)
{
	for(int i = 0; i < A.size(); ++i)
	{
		for(int j = 0; j < A.size(); ++j)
			if(i != j)
				A[i][j] = -A[i][j] / A[i][i];
		A[i].push_back(b[i] / A[i][i]);
		A[i].erase(A[i].begin() + i);
	}
}

void x0(vector<long double>& x, const vector<long double>& b)
{
	for(int i = 0; i < b.size(); ++i)
	{
		long double in;
		cin >> in;
		x.push_back(in);
	}
}

void iterate(const vector< vector<long double> >& A, vector<long double>& x)
{
	for(int i = 0; i < A.size(); ++i)
	{
		x[i] = 0;
		int ix(0), j(0);
		for(; j < A.size() - 1; ++j, ++ix)
		{
			if(ix == i) ++ix;
			x[i] += A[i][j] * x[ix];
		}
		x[i] += A[i][j];
	}
}

int main()
{
	vector< vector<long double> > A;
	vector<long double> b;
	ifstream data("E:\\重要文档\\programs\\数值分析\\接线性方程组的迭代法\\Gauss-Seidel迭代法\\GS.txt");
	if(!data) cerr << "文件打开失败！" << endl;
	else
	{
		int n;
		data >> n;
		cout << n << endl;

		for(int i = 0; i < n; ++i)
		{
			vector<long double> Ai;
			A.push_back(Ai);
			for(int j = 0; j < n; ++j)
			{
				long double Aij;
				data >> Aij;
				A[i].push_back(Aij);
			}

			long double bi;
			data >> bi;
			b.push_back(bi);
		}
		data.close();
	}
	
	output(A); cout << endl;
	outputv(b); cout << endl;
	vector<long double> x;
	
	pretreat(A, b);
	output(A); cout << endl;
	outputv(b); cout << endl;
	B(A, b);
	output(A); cout << endl;
	x0(x, b);
	
	for(int i = 0; i < ITNUM; ++i)
	{
		iterate(A, x);
		outputv(x); cout << endl;
	}
	
	
	//iterate(A, x);
	//outputv(x); cout << endl;
	//iterate(A, x);
	//outputv(x); cout << endl;

	return 0;
}