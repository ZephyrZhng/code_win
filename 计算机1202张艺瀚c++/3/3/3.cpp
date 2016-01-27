#include <iostream>
#include <cmath>
using namespace std;

float Convert(float TempFer)
{
	return (TempFer - 32)* 5/9;
}

int main()
{
	float F;
	
	cout << "Please input the value of F: ";
	cin >> F;
	cout << "The value of C is: " << Convert(F) << endl;

	return 0;
}