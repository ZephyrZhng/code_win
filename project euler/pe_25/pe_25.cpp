/*
project euler problem 25
The Fibonacci sequence is defined by the recurrence relation:
Fn = Fn1 + Fn2, where F1 = 1 and F2 = 1.
Hence the first 12 terms will be:
F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F10 = 55
F11 = 89
F12 = 144
The 12th term, F12, is the first term to contain three digits.
What is the first term in the Fibonacci sequence to contain 1000 digits?
*/
//4782
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define upplimit 1000
typedef string bigint;

class BigInt
{
public:
	BigInt(){}
	~BigInt(){}
	BigInt& operator =(const int& a)
	{
		v.clear();
		for(int b = a; b > 0; b /= 10)
			v.insert(v.begin(), b % 10);
		return *this;
	}
	BigInt& operator =(const BigInt& a)
	{
		v.clear();
		v.resize(a.v.size());
		copy(a.v.begin(), a.v.end(), v.begin());
		return  *this;
	}
	int len()
	{
		return v.size();
	}
	friend ostream& operator <<(ostream& output, const BigInt& a)
	{
		for(int i = 0; i < a.v.size(); ++i)
			output << a.v[i];
		return output;
	}
	friend BigInt operator +(const BigInt& a, const BigInt& b)
	{
		BigInt LONG, SHORT, ans;
		ans.v.clear();
		LONG = a.v.size() > b.v.size()? a: b;
		SHORT = a.v.size() <= b.v.size()? a: b;
		reverse(LONG.v.begin(), LONG.v.end());
		reverse(SHORT.v.begin(), SHORT.v.end());

		int i, carry(0);
		for(i = 0; i < SHORT.v.size(); ++i)
		{
			int temp = LONG.v[i] + SHORT.v[i] + carry;
			ans.v.insert(ans.v.begin(), temp % 10);
			carry = temp / 10;
		}
		for(; i < LONG.v.size(); ++i)
		{
			int temp = LONG.v[i] + carry;
			ans.v.insert(ans.v.begin(), temp % 10);
			carry = temp / 10;
		}
		if(carry)
			ans.v.insert(ans.v.begin(), carry);
		return ans;
	}
private:
	vector<int> v;
};

int main()
{
	vector<BigInt> f(1000000);

	long long n;
	f[0] = f[1] = 1;
	cout << 1 << '\t' << 1 << '\t' << f[0] << endl << 2 << '\t' << 1 << '\t' << f[1] << endl;
	for(n = 2; f[n - 1].len() < upplimit; ++n)
	{
		f[n] = f[n - 1] + f[n - 2];
		cout << n + 1 << '\t' << f[n].len() << '\t' << f[n] << endl;
	}
	cout << n << endl;

	return 0;
}