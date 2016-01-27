#include <iostream>
using namespace std;

const int max = 3;
int matrix[max][max];

void convert()
{
	int i, j, temp;

	for(i = 0; i < max; ++i)
	{
		for(j = i; j < max; ++j)
		{
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
}

void input()
{
	int i, j;

	for(i = 0; i < max; ++i)
	{
		for(j = 0; j < max; ++j)
		{
			cin >> matrix[i][j];
		}
	}
}


void output()
{
	int i, j; 
	
	for(i = 0; i < max; ++i)
	{
		for(j = 0; j < max; ++j)
		{
			cout << matrix[i][j] << " ";			
		}
		cout << endl;
	}
}


int main()
{
	input();
	cout << endl;
	output();
	cout << endl;
	convert();
	output();

	return 0;
}