//Cholesky decomposition
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

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

void CholeskyDecomposition(vector< vector<long double> >& A)
{
	A[0][0] = sqrt(A[0][0]);
	for(int i = 1; i < A.size(); ++i)
		A[i][0] /= A[0][0];
	
	for(int i = 1; i < A.size(); ++i)
	{
		for(int j = 0; j < i; ++j)
			A[i][i] -= A[i][j] * A[i][j];
		A[i][i] = sqrt(A[i][i]);

		for(int ii = i + 1; ii < A.size(); ++ii)
		{
			for(int jj = 0; jj < i; ++jj)
				A[ii][i] -= A[ii][jj] * A[i][jj];
			A[ii][i] /= A[i][i];
		}
	}

	for(int i = 1; i < A.size(); ++i)
		for(int j = 0; j < i; ++j)
			A[j][i] = A[i][j];
}

void back_substitute_downward(const vector< vector<long double> >& G, vector<long double>& y)
{
	for(int i = 0; i < G.size(); ++i)
	{
		if(!i)
			y[i] /= G[i][0];
		else
		{
			for(int j = 0; j <= i - 1; ++j)
				y[i] -= G[i][j] * y[j];
			y[i] /= G[i][i];
		}
	}
}

void back_substitute_upward(const vector< vector<long double> >& GT, vector<long double>& x)
{
	for(int i = GT.size() - 1; i >= 0; --i)
		if(i == GT.size() - 1)
			x[i] /= GT[i][GT.size() - 1];
		else
		{
			for(int j = GT.size() - 1; j >= i + 1; --j)
				x[i] -= GT[i][j] * x[j];
			x[i] /= GT[i][i];
		}
}

int main()
{
	vector< vector<long double> > A;
	vector<long double> b;
	ifstream data("E:\\重要文档\\programs\\数值分析\\解线性方程组的直接方法\\乔列斯基分解\\cholesky.txt");
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

	cout << endl; output(A); cout << endl;
	outputv(b); cout << endl;

	CholeskyDecomposition(A);
	output(A); cout << endl;

	back_substitute_downward(A, b);
	outputv(b); cout << endl;
	back_substitute_upward(A, b);
	outputv(b); cout << endl;

	return 0;
}