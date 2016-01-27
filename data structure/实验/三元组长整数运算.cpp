#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

const int LEN = 9;
const int EXP = 1000000000;

void display(const vector<int>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i];
	cout << endl;
}

void s2v(const string& s, vector<int>& v)
{
	for(int i = 0; i < s.size(); ++i)
		v.push_back(s[i] - '0');
}

void i2v(int i, vector<int>& v)
{
	for(int x = i; x > 0; x /= 10)
		v.insert(v.begin(), x % 10);
	int len = v.size();
	for(int i = 0; i < LEN - len; ++i)
		v.insert(v.begin(), 0);
}

int v2i(const vector<int>& v)
{
	int ans(0);
	for(int i = 0; i < v.size(); ++i)
	{
		ans *= 10;
		ans += v[i];
	}
	return ans;
}

class BigInt
{
public:
	BigInt(){}

	BigInt(const vector< vector<int> >& _v): v(_v){}

	BigInt(int i)
	{
		vector<int> iv;
		for(int x = i; x > 0; x /= 10)
			iv.insert(iv.begin(), x % 10);
		int len = iv.size();
		for(int i = 0; i < LEN * 3 - len; ++i)
			iv.insert(iv.begin(), 0);
		for(int i = 0; i < 3; ++i)
		{
			vector<int> vi(LEN);
			copy(iv.end() - LEN, iv.end(), vi.begin());
			iv.erase(iv.end() - LEN, iv.end());
			v.insert(v.begin(), vi);
		}
	}

	~BigInt(){}

	friend istream& operator >>(istream& input, BigInt& a)
	{
		string s;
		input >> s;
		vector<int> v;
		s2v(s, v);
		int len = v.size();
		for(int i = 0; i < LEN * 3 - len; ++i)
			v.insert(v.begin(), 0);
		for(int i = 0; i < 3; ++i)
		{
			vector<int> vi(LEN);
			copy(v.end() - LEN, v.end(), vi.begin());
			v.erase(v.end() - LEN, v.end());
			a.v.insert(a.v.begin(), vi);
		}
		return input;
	}

	friend ostream& operator <<(ostream& output, const BigInt& a)
	{
		bool flag(false);
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < LEN; ++j)
			{
				if(a.v[i][j])
					flag = true;
				if(flag) output << a.v[i][j];
			}
		return output;
	}

	friend BigInt operator +(const BigInt& a, const BigInt& b)
	{
		vector< vector<int> > ansv;
		int carry(0);
		for(int i = 2; i >= 0; --i)
		{
			int ia = v2i(a.v[i]), ib = v2i(b.v[i]);
			int iab = ia + ib + carry;
			vector<int> vab;
			i2v(iab, vab);
			if(vab.size() > LEN)
			{
				carry = vab[0];
				vab.erase(vab.begin());
			}
			else carry = 0;
			vector<int> vi(LEN);
			copy(vab.begin(), vab.end(), vi.begin());
			ansv.insert(ansv.begin(), vab);
		}
		BigInt ans(ansv);
		return ans;
	}

	BigInt& operator =(const BigInt& a)
	{
		v.clear();
		v.resize(a.v.size());
		copy(a.v.begin(), a.v.end(), v.begin());
		return *this;
	}
private:
	vector< vector<int> > v;
};

int main()
{
	/*
	long long aa(9999999999), bb(1);
	cout << aa + bb << endl;
	BigInt a, b;
	cin >> a >> b;
	BigInt c = a + b;
	cout << c << endl;
	*/
	BigInt a(123546464);
	cout << a << endl;

	return 0;
}