#include <iostream>
using namespace std;

class Animal
{
	public:
		int age;
};

class dog: public Animal
{
	public:
		void SetAge(int n);
};
void dog::SetAge(int n)
{
	age = n;
}

int main()
{
	dog snoopy;

	int a;
	cout << "Please input age of snoopy: ";
	cin >> a;
	snoopy.SetAge(a);
	cout << "Age of snoopy is: " << snoopy.age << endl;

	return 0;
}

