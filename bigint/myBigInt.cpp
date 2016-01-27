#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
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

int main()
{
	BigInt a(54763), b(2356);
	cout << a / b << endl;

	return 0;
}