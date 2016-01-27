#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
#include <windows.h>

using namespace std;

/*
problem 56
A googol (10^100) is a massive number: one followed by one-hundred zeros;
100^100 is almost unimaginably large: one followed by two-hundred zeros.
Despite their size, the sum of the digits in each number is only 1.
Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
*/
//972

template<class T>
void ttov(const T& t, vector<int>& v)
{
	for(T i = t; i > 0; i /= 10)
		v.push_back(i % 10);
	reverse(v.begin(), v.end());
}

void stov(const string& s, vector<int>& v)
{
	for(int i = 0; i < s.size(); ++i)
		v.push_back(s[i] - '0');
}

class BigInt
{
public:
	BigInt(){}

	template<class T>
	BigInt(const T& t)
	{
		v.clear();
		for(T i = t; i > 0; i /= 10)
			v.insert(v.begin(), i % 10);
	}

	BigInt(const vector<int>& vec): v(vec){}

	~BigInt(){}

	template<class T>
	BigInt& operator =(const T& t)
	{
		v.clear();
		for(T i = t; i > 0; i /= 10)
			v.insert(v.begin(), i % 10);
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

	friend istream& operator >>(istream& input, BigInt& a)
	{
		string s;
		input >> s;
		vector<int> temp;
		stov(s, temp);
		a.v = temp;
		return input;
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

	template<class T>
	friend BigInt operator +(const BigInt& a, const T& t)
	{
		vector<int> v;
		ttov(t, v);
		BigInt temp(v);
		return temp + a;
	}

	template<class T>
	friend BigInt operator +(const T& t, const BigInt& a)
	{
		return a + t;
	}

	BigInt& operator +=(const BigInt& a)
	{
		*this = *this + a;
		return *this;
	}

	template<class T>
	BigInt& operator +=(const T& t)
	{
		*this = *this + t;
		return *this;
	}

	friend BigInt operator *(const BigInt& a, const BigInt& b)
	{
		BigInt LONG, SHORT, ans;
		ans.v.clear();
		LONG = a.v.size() > b.v.size()? a: b;
		SHORT = a.v.size() <= b.v.size()? a: b;
		reverse(LONG.v.begin(), LONG.v.end());
		reverse(SHORT.v.begin(), SHORT.v.end());
		vector<BigInt> inter(SHORT.v.size());

		for(int i = 0; i < SHORT.v.size(); ++i)
		{
			vector<int> tempv;
			int carry(0);
			for(int j = 0; j < LONG.v.size(); ++j)
			{
				int temp = SHORT.v[i] * LONG.v[j] + carry;
				tempv.insert(tempv.begin(), temp % 10);
				carry = temp / 10;
			}
			if(carry)
				tempv.insert(tempv.begin(), carry);
			for(int j = 0; j < i; ++j)
				tempv.push_back(0);
			BigInt tempi(tempv);
			inter.push_back(tempi);
		}

		for(int i = 0; i < inter.size(); ++i)
			ans += inter[i];
		return ans;
	}

	template<class T>
	friend BigInt operator *(const BigInt& a, const T& t)
	{
		vector<int> v;
		ttov(t, v);
		BigInt temp(v);
		return temp * a;
	}

	template<class T>
	friend BigInt operator *(const T& t, BigInt& a)
	{
		return a * t;
	}

	BigInt& operator *=(const BigInt& a)
	{
		*this = *this * a;
		return *this;
	}

	template<class T>
	BigInt& operator *=(const T& t)
	{
		*this = *this * t;
		return *this;
	}

	friend bool operator ==(const BigInt& a, const BigInt& b)
	{
		if(a.v.size() != b.v.size()) return false;
		for(int i = 0; i < a.v.size(); ++i)
			if(a.v[i] != b.v[i])
				return false;
		return true;
	}

	template<class T>
	friend bool operator ==(const BigInt& a, const T& t)
	{
		vector<int> v;
		ttov(t, v);
		BigInt temp(v);
		return a == temp;
	}

	template<class T>
	friend bool operator ==(const T& t, const BigInt& a)
	{
		return a == t;
	}

	friend bool operator !=(const BigInt& a, const BigInt& b)
	{
		return !(a == b);
	}

	template<class T>
	friend bool operator !=(const BigInt& a, const T& t)
	{
		return !(a == t);
	}

	template<class T>
	friend bool operator !=(const T& t, const BigInt& a)
	{
		return !(t == a);
	}

	friend bool operator >(const BigInt& a, const BigInt& b)
	{
		if(a.v.size() > b.v.size()) return true;
		else if(a.v.size() < b.v.size()) return false;
		else
			for(int i = 0; i < a.v.size(); ++i)
				if(a.v[i] > b.v[i]) return true;
				else if(a.v[i] < b.v[i]) return false;
		return false;
	}

	template<class T>
	friend bool operator >(const BigInt& a, const T& t)
	{
		vector<int> v;
		ttov(t, v);
		BigInt temp(v);
		return a > temp;
	}

	template<class T>
	friend bool operator>(const T& t, const BigInt& a)
	{
		if(a > t || a == t) return false;
		return true;
	}

	friend bool operator >=(const BigInt& a, const BigInt& b)
	{
		return (a > b || a == b);
	}

	template<class T>
	friend bool operator >=(const BigInt& a, const T& t)
	{
		return (a > t || a == t);
	}

	template<class T>
	friend bool operator >=(const T& t, const BigInt& a)
	{
		return (t > a || t == a);
	}

	friend bool operator <(const BigInt& a, const BigInt& b)
	{
		return !(a >= b);
	}

	template<class T>
	friend bool operator <(const BigInt& a, const T& t)
	{
		return !(a >= t);
	}

	template<class T>
	friend bool operator <(const T& t, const BigInt& a)
	{
		return !(t >= a);
	}

	friend bool operator <=(const BigInt& a, const BigInt& b)
	{
		return !(a > b);
	}

	template<class T>
	friend bool operator <=(const BigInt& a, const T& t)
	{
		return !(a > t);
	}

	template<class T>
	friend bool operator <=(const T& t, const BigInt& a)
	{
		return !(t > a);
	}

	BigInt pow(const BigInt& power)
	{
		BigInt result = 1;
		for(BigInt i = 0; i < power; i += 1)
		{
			result *= *this;
		}
		return result;
	}

	template<class T>
	BigInt pow(const T& t)
	{
		BigInt result = 1;
		for(BigInt i = 0; i < t; i += 1)
		{
			result *= t;
		}
		return result;
	}

	vector<int> v;
};

int main()
{
	int maxDigitSum = 0;
	for(BigInt _base = 0; _base < 100; _base += 1)
	{
		for(BigInt _power = 0; _power < 100; _power += 1)
		{
			BigInt base(_base);
			BigInt p = base.pow(_power);
			cout << p << endl;

			int digitSum = 0;
			for(int i = 0; i < p.v.size(); ++i)
			{
				digitSum += p.v[i];
			}

			cout << digitSum << endl << endl;

			if(digitSum > maxDigitSum)
			{
				maxDigitSum = digitSum;
			}
		}
	}

	cout << maxDigitSum << endl;

	return 0;
}