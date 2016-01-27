#include <iostream>
#include <cmath>
using namespace std;

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int max(int a, int b, int c)
{
	return (a > max(b, c)) ? a : max(b, c); 
}

double max(double a, double b)
{
	return (a > b) ? a : b; 
}

double max(double a, double b, double c)
{
	return (a > max(b, c)) ? a : max(b, c); 
}

int main()
{
	int a, b, c;
	float x, y, z;

	cout << "Please input 2 int numbers: ";
	cin >> a >> b;
	cout << "The maximum of these 2 int numbers is: " << max(a, b) << endl;

	cout << "Please input 3 int numbers: ";
	cin >> a >> b >> c;
	cout << "The maximum of these 3 int numbers is: " << max(a, b, c) << endl;

	cout << "Please input 2 double numbers: ";
	cin >> x >> y;
	cout << "The maximum of these 2 double numbers is: " << max(x, y) << endl;
	
	cout << "Please input 3 double numbers: ";
	cin >> x >> y >> z;
	cout << "The maximum of these 3 double numbers is: " << max(x, y, z) << endl;

	return 0;
}