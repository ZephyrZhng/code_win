#include <iostream>
using namespace std;

int main()
{
	int sum;
	int i;
	for(sum = 0,i = 1; i <= 10; ++i)
	{
		sum += i;
	}
	cout << sum << endl;
	return 0;
}