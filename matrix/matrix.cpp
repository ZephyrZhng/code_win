#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
#include <windows.h>

using namespace std;

class MATRIX
{
public:
	MATRIX() {}
	MATRIX(int _row, int _column);
	MATRIX(string file_path);
	MATRIX(const vector< vector<double> >& _matrix);
	MATRIX(const MATRIX& _matrix);

	void allocate(int _row, int _column);
	void load(const vector< vector<double> >& _matrix);
	void load(MATRIX _matrix);

	void display();

	void add(const MATRIX& _matrix, MATRIX& result_matrix);
	void scalar_multiply(double multiplier, MATRIX& result_matrix);
	void subtract(const MATRIX& _matrix, MATRIX& result_matrix);
	void multiply(const MATRIX& _matrix, MATRIX& result_matrix);
	void convert_into_upper_unitriangular_matrix();
	void invert(MATRIX& result_matrix);
	double get_determinant();
	int get_rank();
	void calculate_eigenvalue(vector<double>& eigenvalue);
	int get_trace();

	int row;
	int column;
	vector< vector<double> > matrix;
private:
};

MATRIX::MATRIX(int _row, int _column): row(_row), column(_column)
{
	for(int i = 0; i < row; ++i)
	{
		matrix.push_back(vector<double>(column));
	}
}

MATRIX::MATRIX(string file_path)
{
	ifstream matrix_file(file_path);
	matrix_file >> row >> column;
	for(int i = 0; i < row; ++i)
	{
		matrix.push_back(vector<double>(column));
		for(int j = 0; j < column; ++j)
		{
			matrix_file >> matrix[i][j];
		}
	}
	matrix_file.close();
}

MATRIX::MATRIX(const vector< vector<double> >& _matrix)
{
	row = _matrix.size();
	column = _matrix[0].size();
	for(int i = 0; i < row; ++i)
	{
		matrix.push_back(vector<double>(column));
		for(int j = 0; j < column; ++j)
		{
			matrix[i][j] = _matrix[i][j];
		}
	}
}

MATRIX::MATRIX(const MATRIX& _matrix): row(_matrix.row), column(_matrix.column)
{
	for(int i = 0; i < row; ++i)
	{
		matrix.push_back(vector<double>(column));
		for(int j = 0; j < column; ++j)
		{
			matrix[i][j] = _matrix.matrix[i][j];
		}
	}
}

void MATRIX::allocate(int _row, int _column)
{
	row = _row;
	column = _column;
	for(int i = 0; i < row; ++i)
	{
		matrix.push_back(vector<double>(column));
	}
}

void MATRIX::load(const vector< vector<double> >& _matrix)
{
	matrix.clear();
	row = _matrix.size();
	column = _matrix[0].size();
	for(int i = 0; i < row; ++i)
	{
		matrix.push_back(vector<double>(column));
		for(int j = 0; j < column; ++j)
		{
			matrix[i][j] = _matrix[i][j];
		}
	}
}

void MATRIX::load(MATRIX _matrix)
{
	row = _matrix.row;
	column = _matrix.column;
	matrix.clear();
	for(int i = 0; i < row; ++i)
	{
		matrix.push_back(vector<double>(column));
		for(int j = 0; j < column; ++j)
		{
			matrix[i][j] = _matrix.matrix[i][j];
		}
	}
}

void MATRIX::display()
{
	for(int i = 0; i < row; ++i)
	{
		for(auto& p: matrix[i])
		{
			cout << p << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void MATRIX::add(const MATRIX& _matrix, MATRIX& result_matrix)
{
	if(row != _matrix.row || column != _matrix.column)
	{
		cout << "error: two matrices with different scales added!" << endl;
		return;
	}
	result_matrix.allocate(row, column);
	for(int i = 0; i < row; ++i)
	{
		for(int j = 0; j < column; ++j)
		{
			result_matrix.matrix[i][j] = matrix[i][j] + _matrix.matrix[i][j];
		}
	}
}

void MATRIX::scalar_multiply(double multiplier, MATRIX& result_matrix)
{
	for(int i = 0; i < row; ++i)
	{
		for(int j = 0; j < column; ++j)
		{
			matrix[i][j] *= multiplier;
		}
	}
}

void MATRIX::subtract(const MATRIX& _matrix, MATRIX& result_matrix)
{
	if(row != _matrix.row || column != _matrix.column)
	{
		cout << "error: two matrices with different scales subtracted!" << endl;
		return;
	}
	result_matrix.allocate(row, column);
	for(int i = 0; i < row; ++i)
	{
		for(int j = 0; j < column; ++j)
		{
			result_matrix.matrix[i][j] = matrix[i][j] - _matrix.matrix[i][j];
		}
	}
}

void MATRIX::multiply(const MATRIX& _matrix, MATRIX& result_matrix)
{
	if(column != _matrix.row)
	{
		cout << "error: two matrices with different scales multiplied!" << endl;
		return;
	}
	result_matrix.allocate(row, _matrix.column);
	for(int i = 0; i < result_matrix.column; ++i)
	{
		for(int j = 0; j < result_matrix.row; ++j)
		{
			for(int k = 0; k < result_matrix.column; ++k)
			{
				result_matrix.matrix[j][i] += matrix[j][k] * _matrix.matrix[k][i];
			}
		}
	}
}

void MATRIX::convert_into_upper_unitriangular_matrix()
{
	for(int i = 0; i < row; ++i)
	{
		double _coefficient = matrix[i][i];
		for(int j = i; j < column; ++j)
		{
			matrix[i][j] /= _coefficient;
		}
		for(int j = i + 1; j < row; ++j)
		{
			double coefficient = matrix[j][i];
			for(int k = i; k < column; ++k)
			{
				matrix[j][k] -= coefficient * matrix[i][k];
			}
		}
	}
}

void MATRIX::invert(MATRIX& result_matrix)
{
	if(row != column)
	{
		cout << "error: a non-square matrix inverted!" << endl;
		return;
	}

	MATRIX tmp_matrix(matrix);
	int n = tmp_matrix.row;

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			double element = (i == j)? 1: 0;
			tmp_matrix.matrix[i].push_back(element);
		}
	}

	tmp_matrix.column += n;

	tmp_matrix.convert_into_upper_unitriangular_matrix();

	for(int i = n - 1; i >= 0; --i)
	{
		for(int j = i - 1; j >= 0; --j)
		{
			double coefficient = tmp_matrix.matrix[j][i];
			for(int k = i; k < column; ++k)
			{
				tmp_matrix.matrix[j][k] -= coefficient * tmp_matrix.matrix[i][k];
			}
		}
	}

	result_matrix.allocate(n, n);
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			result_matrix.matrix[i][j] = tmp_matrix.matrix[i][j + n];
		}
	}
}

double MATRIX::get_determinant()
{
	MATRIX tmp_matrix(matrix);
	tmp_matrix.convert_into_upper_unitriangular_matrix();

	int n = tmp_matrix.row;
	double matrix_determinant = tmp_matrix.matrix[0][0];
	for(int i = 1; i < n; ++i)
	{
		matrix_determinant *= tmp_matrix.matrix[i][i];
	}

	return matrix_determinant;
}

int MATRIX::get_rank()
{
	MATRIX tmp_matrix(matrix);
	tmp_matrix.convert_into_upper_unitriangular_matrix();

	int n = tmp_matrix.row;
	int matrix_rank = 0;
	for(int i = 0; i < n; ++i)
	{
		if(tmp_matrix.matrix[i][i])
		{
			++matrix_rank;
		}
	}

	return matrix_rank;
}

void MATRIX::calculate_eigenvalue(vector<double>& eigenvalue)
{

}

int MATRIX::get_trace()
{
	
}

int main()
{
	
	
	return 0;
}