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

template<typename T>
void ttov(const T& t, vector<int>& v)
{
	if(t == 0)
	{
		v.push_back(0);
		return;
	}
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

	template<typename T>
	BigInt(const T& t)
	{
		if(t == 0)
		{
			v.push_back(0);
			return;
		}
		v.clear();
		for(T i = t; i > 0; i /= 10)
			v.insert(v.begin(), i % 10);
	}

	BigInt(const vector<int>& vec): v(vec){}

	~BigInt(){}

	template<typename T>
	BigInt& operator =(const T& t)
	{
		if(t == 0)
		{
			v.push_back(0);
			return *this;
		}
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

	template<typename T>
	friend BigInt operator +(const BigInt& a, const T& t)
	{
		return a + BigInt(t);
	}

	template<typename T>
	friend BigInt operator +(const T& t, const BigInt& a)
	{
		return a + t;
	}

	BigInt& operator +=(const BigInt& a)
	{
		*this = *this + a;
		return *this;
	}

	template<typename T>
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
		if(ans.v[0] == 0)
		{
			ans.v.clear();
			ans.v.push_back(0);
		}
		return ans;
	}

	template<typename T>
	friend BigInt operator *(const BigInt& a, const T& t)
	{
		return a * BigInt(t);
	}

	template<typename T>
	friend BigInt operator *(const T& t, BigInt& a)
	{
		return a * t;
	}

	BigInt& operator *=(const BigInt& a)
	{
		*this = *this * a;
		return *this;
	}

	template<typename T>
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

	template<typename T>
	friend bool operator ==(const BigInt& a, const T& t)
	{
		return a == BigInt(t);
	}

	template<typename T>
	friend bool operator ==(const T& t, const BigInt& a)
	{
		return a == t;
	}

	friend bool operator !=(const BigInt& a, const BigInt& b)
	{
		return !(a == b);
	}

	template<typename T>
	friend bool operator !=(const BigInt& a, const T& t)
	{
		return !(a == t);
	}

	template<typename T>
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

	template<typename T>
	friend bool operator >(const BigInt& a, const T& t)
	{
		return a > BigInt(t);
	}

	template<typename T>
	friend bool operator>(const T& t, const BigInt& a)
	{
		if(a > t || a == t) return false;
		return true;
	}

	friend bool operator >=(const BigInt& a, const BigInt& b)
	{
		return (a > b || a == b);
	}

	template<typename T>
	friend bool operator >=(const BigInt& a, const T& t)
	{
		return (a > t || a == t);
	}

	template<typename T>
	friend bool operator >=(const T& t, const BigInt& a)
	{
		return (t > a || t == a);
	}

	friend bool operator <(const BigInt& a, const BigInt& b)
	{
		return !(a >= b);
	}

	template<typename T>
	friend bool operator <(const BigInt& a, const T& t)
	{
		return !(a >= t);
	}

	template<typename T>
	friend bool operator <(const T& t, const BigInt& a)
	{
		return !(t >= a);
	}

	friend bool operator <=(const BigInt& a, const BigInt& b)
	{
		return !(a > b);
	}

	template<typename T>
	friend bool operator <=(const BigInt& a, const T& t)
	{
		return !(a > t);
	}

	template<typename T>
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

	template<typename T>
	BigInt pow(const T& t)
	{
		BigInt result = 1;
		for(BigInt i = 0; i < t; i += 1)
		{
			result *= t;
		}
		return result;
	}

	friend BigInt operator -(const BigInt& a, const BigInt& b)
	// work well only when a > b
	{
		BigInt LONG(a), SHORT(b), ans;
		ans.v.clear();
		reverse(LONG.v.begin(), LONG.v.end());
		reverse(SHORT.v.begin(), SHORT.v.end());

		int i, borrow(0);
		for(i = 0; i < SHORT.v.size(); ++i)
		{
			int temp = LONG.v[i] - SHORT.v[i] + borrow;
			if(temp < 0)
			{
				temp  += 10;
				borrow = -1;
			}
			else
			{
				borrow = 0;
			}
			ans.v.insert(ans.v.begin(), temp);
		}
		for(; i < LONG.v.size(); ++i)
		{
			int temp = LONG.v[i] + borrow;
			if(temp < 0)
			{
				temp  += 10;
				borrow = -1;
			}
			else
			{
				borrow = 0;
			}
			ans.v.insert(ans.v.begin(), temp);
		}
		int ans_size = ans.v.size();
		for(int i = 0; i < ans_size; ++i)
		{
			if(!*(ans.v.begin()))
			{
				ans.v.erase(ans.v.begin());
			}
			else
			{
				break;
			}
		}
		if(ans.v.empty())
		{
			ans.v.push_back(0);
		}
		return ans;
	}

	template<typename T>
	friend BigInt operator -(const BigInt& a, const T& t)
	{
		return a - BigInt(t);
	}

	template<typename T>
	friend BigInt operator -(const T& t, const BigInt& a)
	{
		return BigInt(t) - a;
	}

	BigInt& operator -=(const BigInt& a)
	{
		*this = *this - a;
		return *this;
	}

	template<typename T>
	BigInt& operator -=(const T& t)
	{
		*this -= BigInt(t);
		return *this;
	}

	void operator ++()
	{
		*this += 1;
	}

	void operator --()
	{
		*this -= 1;
	}

	friend BigInt operator /(const BigInt& a, const BigInt& b)
	{
		BigInt i(0);
		for(; i * b <= a; i += 1);
		return i - 1;
	}

	template<typename T>
	friend BigInt operator /(const BigInt& a, const T& t)
	{
		return a / BigInt(t);
	}

	template<typename T>
	friend BigInt operator /(const T& t, const BigInt& a)
	{
		return BigInt(t) / a;
	}

	BigInt& operator /=(const BigInt& a)
	{
		*this = *this / a;
		return *this;
	}

	template<typename T>
	BigInt& operator /=(const T& t)
	{
		*this /= BigInt(t);
		return *this;
	}

	friend BigInt operator %(const BigInt& a, const BigInt& b)
	{
		BigInt c(a);
		for(; c >= b; c = c - b);
		return c;
	}

	template<typename T>
	friend BigInt operator %(const BigInt& a, const T& t)
	{
		return a % BigInt(t);
	}

	template<typename T>
	friend BigInt operator %(const T& t, const BigInt& a)
	{
		return BigInt(t) % a;
	}

private:
	vector<int> v;
};

class Frac
{
public:
	Frac() {}
	Frac(const Frac& _frac): num(_frac.num), den(_frac.den) {}
	Frac(BigInt _num, BigInt _den): num(_num), den(_den) {}

	Frac& operator =(const Frac& frac)
	{
		num = frac.num;
		den = frac.den;
		return *this;
	}

	BigInt num;
	BigInt den;
};

BigInt gcd(BigInt a, BigInt b)
// tooooooooooooooooooooooooooo slowwwwwwwwwwwwwwwwwwwwwwwww
{
	BigInt ans = (a < b)? a: b;
	BigInt c   = (a < b)? a: b;
	BigInt big = (a > b)? a: b;
	for(; ans > 0; ans = ans - 1)
	{
		if(big % ans == 0 && c % ans == 0)
		{
			return ans;
		}
	}
}

BigInt lcm(BigInt a, BigInt b)
{
	return a * b / gcd(a, b);
}

class fraction
{
public:
	fraction() {}

	template<typename T>
	fraction(const T& _a)
	{
		frac.num      = _a;
		frac.den      = 1;
	}

	fraction(const fraction& _frac): frac(_frac.frac)
	{
		simplify();
	}

	fraction(BigInt _num, BigInt _den): frac(Frac(_num, _den))
	{
		simplify();
	}

	fraction(BigInt _integer, BigInt _num, BigInt _den): frac(Frac(_integer * _den + _num, _den))
	{
		simplify();
	}

	void simplify()
	{
		BigInt gcd_num_den_frac = gcd(frac.num, frac.den);
		frac.num                = frac.num / gcd_num_den_frac;
		frac.den                = frac.den / gcd_num_den_frac;
	}

	void outputFracForm()
	{
		cout << frac.num << "/" << frac.den << endl;
	}

	friend fraction operator +(const fraction& a, const fraction& b)
	{
		BigInt lcm_den1_den2 = lcm(a.frac.den, b.frac.den);
		BigInt coefficient1  = lcm_den1_den2 / a.frac.den;
		BigInt coefficient2  = lcm_den1_den2 / b.frac.den;
		return fraction(a.frac.num * coefficient1 + b.frac.num * coefficient2, lcm_den1_den2);
	}

	template<typename T>
	friend fraction operator +(const fraction& a, const T& b)
	{
		return a + fraction(b);
	}

	template<typename T>
	friend fraction operator +(const T& a, const fraction& b)
	{
		return fraction(a) + b;
	}

	friend fraction operator -(const fraction& a, const fraction& b)
	{
		BigInt lcm_den1_den2 = lcm(a.frac.den, b.frac.den);
		BigInt coefficient1  = lcm_den1_den2 / a.frac.den;
		BigInt coefficient2  = lcm_den1_den2 / b.frac.den;
		return fraction(a.frac.num * coefficient1 - b.frac.num * coefficient2, lcm_den1_den2);
	}

	template<typename T>
	friend fraction operator -(const fraction& a, const T& b)
	{
		return a - fraction(b);
	}

	template<typename T>
	friend fraction operator -(const T& a, const fraction& b)
	{
		return fraction(a) - b;
	}

	friend fraction operator *(const fraction& a, const fraction& b)
	{
		return fraction(a.frac.num * b.frac.num, a.frac.den * b.frac.den);
	}

	template<typename T>
	friend fraction operator *(const fraction& a, const T& b)
	{
		return a * fraction(b);
	}

	template<typename T>
	friend fraction operator *(const T& a, const fraction& b)
	{
		return fraction(a) * b;
	}

	friend fraction operator /(const fraction& a, const fraction& b)
	{
		return fraction(a.frac.num * b.frac.den, a.frac.den * b.frac.num);
	}

	template<typename T>
	friend fraction operator /(const fraction& a, const T& b)
	{
		return a / fraction(b);
	}

	template<typename T>
	friend fraction operator /(const T& a, const fraction& b)
	{
		return fraction(a) / b;
	}

	fraction& operator =(const fraction& _a)
	{
		frac = _a.frac;
		return *this;
	}

	template<typename T>
	fraction& operator =(const T& a)
	{
		*this = fraction(a);
		return *this;
	}

	bool operator <(const fraction& _a)
	{
		BigInt lcm_den1_den2 = lcm(frac.den, _a.frac.den);
		BigInt  coefficient  = lcm_den1_den2 /    frac.den;
		BigInt _coefficient  = lcm_den1_den2 / _a.frac.den;
		return frac.num * coefficient < _a.frac.num * _coefficient;
	}
	
	template<typename T>
	bool operator <(const T& _a)
	{
		return *this < fraction(_a);
	}

	bool operator >(const fraction& _a)
	{
		return !(*this < _a) && !(*this == _a);
	}

	template<typename T>
	bool operator >(const T& _a)
	{
		return *this > fraction(_a);
	}

	bool operator ==(const fraction& _a)
	{
		return (
			frac.num == _a.frac.num && frac.den == _a.frac.den
		);
	}

	template<typename T>
	bool operator ==(const T& _a)
	{
		return (*this == fraction(_a));
	}

	bool operator !=(const fraction& _a)
	{
		return !(*this == _a);
	}

	template<typename T>
	bool operator !=(const T& _a)
	{
		return !(*this == _a);
	}

	bool operator >=(const fraction& _a)
	{
		return !(*this < _a);
	}

	template<typename T>
	bool operator >=(const T& _a)
	{
		return !(*this < _a);
	}

	bool operator <=(const fraction& _a)
	{
		return !(*this > _a);
	}

	template<typename T>
	bool operator <=(const T& _a)
	{
		return !(*this > _a);
	}

	// >> <<

	friend ostream& operator <<(ostream& output, const fraction& a)
	{
		output << a.frac.num << "/" << a.frac.den;
		return output;
	}

	Frac frac;
};

int main()
{
	return 0;
}