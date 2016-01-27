#include <iostream>
using namespace std;

template<typename T>
T Max(T x, T y)
{
	return x > y ? x : y;
}

template<typename T>
T Max(T x, T y, T z)
{
	return Max(x, y) > z ? Max(x, y) : z;
}

int main()
{
	int a, b, c;
	double x, y, z;
	
	cout << "Please input 2 integers: ";
	cin >> a >> b;
	cout << "Max of these 2 integers is: " << Max(a, b) << endl;
	cout << "Please input 3 integers: ";
	cin >> a >> b >> c;
	cout << "Max of these 3 integers is: " << Max(a, b, c) << endl;
	cout << "Please input 2 double numbers: ";
	cin >> x >> y;
	cout << "Max of these 3 double numbers is: " << Max(x, y) << endl;
	cout << "Please input 3 double numbers: ";
	cin >> x >> y >> z;
	cout << "Max of these 3 double numbers is: " << Max(x, y, z) << endl;

	return 0;
}
