//直接三角分解
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <vector>
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

void LDLTDecomposition(vector< vector<long double> >& A, vector<long double>& D)
{
	D.push_back(A[0][0]);
	A[0][0] = 1;
	for(int i = 1; i < A.size(); ++i)
		A[i][0] /= D[0];

	for(int i = 1; i < A.size(); ++i)
	{
		D.push_back(A[i][i]);
		for(int j = 0; j < i; ++j)
			D[i] -= A[i][j] * A[i][j] * D[j];

		for(int ii = i + 1; ii < A.size(); ++ii)
		{
			for(int jj = 0; jj < i; ++jj)
				A[ii][i] -= A[ii][jj] * A[i][jj] * D[jj];
			A[ii][i] /= D[i];
		}
	}

	for(int i = 1; i < A.size(); ++i)
		A[i][i] = 1;

	for(int i = 1; i < A.size(); ++i)
		for(int j = 0; j < i; ++j)
			A[j][i] = A[i][j];
}

void back_substitute_downward(const vector< vector<long double> >& L, vector<long double>& y)
{
	for(int i = 0; i < L.size(); ++i)
	{
		if(!i)
			y[i] /= L[i][0];
		else
		{
			for(int j = 0; j <= i - 1; ++j)
				y[i] -= L[i][j] * y[j];
			y[i] /= L[i][i];
		}
	}
}

void back_substitute_upward(const vector< vector<long double> >& LT, 
	const vector<long double> D, vector<long double>& x)
{
	for(int i = 0; i < D.size(); ++i)
		x[i] /= D[i];

	for(int i = LT.size() - 1; i >= 0; --i)
		if(i == LT.size() - 1)
			x[i] /= LT[i][LT.size() - 1];
		else
		{
			for(int j = LT.size() - 1; j >= i + 1; --j)
				x[i] -= LT[i][j] * x[j];
			x[i] /= LT[i][i];
		}
}

int main()
{
	vector< vector<long double> > A;
	vector<long double> b;
	ifstream data("E:\\重要文档\\programs\\数值分析\\解线性方程组的直接方法\\LDT^T分解\\LDL^T.txt");
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

	vector<long double> D;
	LDLTDecomposition(A, D);
	output(A); cout << endl;
	outputv(D); cout << endl;

	back_substitute_downward(A, b);
	outputv(b); cout << endl;
	back_substitute_upward(A, D, b);
	outputv(b); cout << endl;

	return 0;
}