//数制转换
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#define len 10

void _judge_k_stystem(int _num_k, int k)
{
	int flag;

	for(flag = 1; _num_k > 0; _num_k /= 10)
	{
		if((_num_k % 10) >= k)
		{
			flag = 0;
			cout << "The input is not a number in \"";
			cout << k << "\" system." << endl;
			break;
		}
	}
	if(flag)
	{
		cout << "The input is a number in \"";
		cout << k << "\" system." << endl;
	}
}

int reverse(int x)
{
	int _x;

	for(_x = 0 ; x > 0; x /= 10)
	{
		_x *= 10;
		_x += x % 10;
	}

	return _x;
}

int _convert_k1_to_dec(int _num_k1, int k1)
{
	int i;
	int _num_dec;

	for(_num_dec = 0, i = 0; _num_k1 > 0; _num_k1 /= 10, ++i)
	{
		_num_dec += (_num_k1 % 10) * pow(k1, i);
	}

	return _num_dec;
}

int _convert_dec_to_k2(int _num_dec, int k2)
{
	int cnt, i;
	int _num_k2;
	int _num_k2_arr[len];

	memset(_num_k2_arr, 0, sizeof(_num_k2_arr));
	for(cnt = 0; _num_dec > 0; ++cnt)
	{
		_num_k2_arr[cnt] = _num_dec % k2;
		_num_dec = int(_num_dec / k2);
	}
	for(i = cnt - 1, _num_k2 = 0; i >= 0; --i)
	{
		_num_k2 *= 10;
		_num_k2 += _num_k2_arr[i];
	}

	return _num_k2;
}

int _convert_k1_to_k2(int _num_k1, int k1, int k2)
{
	return _convert_dec_to_k2(_convert_k1_to_dec(_num_k1, k1), k2);
}

int main()
{
	int _num_k1, k1, k2;

	cin >> _num_k1 >> k1 >> k2;
	cout << _convert_k1_to_k2(_num_k1, k1, k2) << endl;

	return 0;
}