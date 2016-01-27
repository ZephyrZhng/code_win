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

long double calAij(vector< vector<long double> >& v, int i, int j)
{
	if(i <= j)//求uij
	{
		int _i(0), _j(0);
		for(; _i < i; ++_i, ++_j)
			v[i][j] -= v[_i][j] * v[i][_j];
	}

	else//求lij
	{
		int _i(0), _j(0);
		for(; _j < j; ++_i, ++_j)
			v[i][j] -= v[_i][j] * v[i][_j];
		v[i][j] /= v[j][j];
	}
}

void tridecomposition(vector< vector<long double> >& A)
{
	for(int i = 1; i < A.size(); ++i)
		A[i][0] /= A[0][0];
	
	for(int pos = 1; pos < A.size(); ++pos)
	{
		//计算uij
		for(int j = pos; j < A.size(); ++j)
			calAij(A, pos, j);

		//计算lij
		for(int i = pos + 1; i < A.size(); ++i)
			calAij(A, i, pos);
	}
}

void back_substitute_downward(const vector< vector<long double> >& L, vector<long double>& y)
{
	for(int i = 0; i < L.size(); ++i)
		if(i)
			for(int j = 0; j <= i - 1; ++j)
				y[i] -= L[i][j] * y[j];
}

void back_substitute_upward(const vector< vector<long double> >& U, vector<long double>& x)
{
	for(int i = U.size() - 1; i >= 0; --i)
		if(i == U.size() - 1)
			x[i] /= U[i][U.size() - 1];
		else
		{
			for(int j = U.size() - 1; j >= i + 1; --j)
				x[i] -= U[i][j] * x[j];
			x[i] /= U[i][i];
		}
}

int main()
{
	vector< vector<long double> > A;
	vector<long double> b;
	ifstream data("E:\\重要文档\\programs\\数值分析\\直接三角分解法\\tridecomposition data.txt");
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

	tridecomposition(A);
	output(A); cout << endl;

	back_substitute_downward(A, b);
	outputv(b); cout << endl;
	back_substitute_upward(A, b);
	outputv(b); cout << endl;

	return 0;
}