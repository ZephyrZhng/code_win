#include <iostream>
using namespace std;

const int max = 1000;
char a[max], b[max];

void strcat()
{
	int x, y, z;

	for(x = 0; a[x] != '\0'; ++x);
	for(y = x, z = 0; b[z] != '\0'; ++y, ++z)
	{
		a[y] = b[z];
	}
}

int main()
{
	cout << "Please input 2 character arrays:" << endl;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "Now we concatenate b after a and get:" << endl;
	strcat(a, b);
	cout << a << endl;

	return 0;
}
