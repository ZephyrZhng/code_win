#include <iostream>

using namespace std;

class BaseClass
{
	public:
		BaseClass(int n);
		~BaseClass();
		int Number;
};
BaseClass::BaseClass(int n)
{
	Number = n;
	cout << "BaseClass's concstructor called!" << endl;
}
BaseClass::~BaseClass()
{
	cout << "BaseClass's destructor called!" << endl;
}

class DerivedClass: public BaseClass
{
	public:
		DerivedClass(int n);
		~DerivedClass();
};
DerivedClass::DerivedClass(int n): BaseClass(n)
{
	cout << "DerivedClass's constructor called!" << endl;
}
DerivedClass::~DerivedClass()
{
	cout << "DerivedClass's destructor called!" << endl;
}

int main()
{
	DerivedClass obj(1);

	cout << obj.Number << endl;

	return 0;
}