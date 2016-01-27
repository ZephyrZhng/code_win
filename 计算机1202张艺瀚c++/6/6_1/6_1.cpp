#include <iostream>
using namespace std;

const int max = 3;
int (*p)[max];

void convert(int (*p)[max])
{
	int i, j, temp;

	for(i = 0; i < max; ++i)
	{
		for(j = i; j < max; ++j)
		{
			temp = p[i][j];
			p[i][j] = p[j][i];
			p[j][i] = temp;
		}
	}
}

void input(int (*p)[max])
{
	int i, j;

	for(i = 0; i < max; ++i)
	{
		for(j = 0; j < max; ++j)
		{
			cin >> p[i][j];
		}
	}
}


void output(int (*p)[max])
{
	int i, j; 
	
	for(i = 0; i < max; ++i)
	{
		for(j = 0; j < max; ++j)
		{
			cout << p[i][j] << " ";			
		}
		cout << endl;
	}
}


int main()
{
	p = new int[max][max];
	input(p);
	cout << endl;
	output(p);
	cout << endl;
	convert(p);
	output(p);

	return 0;
}