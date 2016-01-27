#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

int reverse(int x)
{
	int y, len, _x, i;

	for(len = 0, y = x; y > 0; y /= 10, ++len);
	for(i = 0, y = x, _x = 0; i < len; y /= 10, ++i)
	{
		_x += y % 10 * pow(10, len - i - 1);
	}

	return _x;
}

void generate(int x)
{
	int result, cnt;

	for(result = x, cnt = 0; reverse(result) != x; ++cnt)
	{
		cout << cnt + 1 << ". ";
		cout << result << "+" << reverse(result) << "=";
		cout << result + reverse(result) << endl;
		result += reverse(result);
	}
	cout << "We get a palindrome: " << result;
	cout << " from " << x << " via " << cnt << " step(s)." << endl;
}

int main()
{
	int x;

	cout << "Please input a number: ";
	cin >> x;
	generate(x);

	return 0;
}
