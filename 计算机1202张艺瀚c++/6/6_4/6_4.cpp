#include <iostream>
#include <string>

using namespace std;

const int max = 100;

int main()
{
	string arr_1, arr_2;
	cout << "Please input 2 character arrays:" << endl;
	cout << "arr_1 = ";
	cin >> arr_1;
	cout << "arr_2 = ";
	cin >> arr_2;
	cout << "Now we concatenate arr_2 after arr_1 and get:" << endl;
	cout << arr_1 + arr_2 << endl;

	return 0;
}