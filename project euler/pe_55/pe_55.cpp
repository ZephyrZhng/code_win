/*
If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
Not all numbers produce palindromes so quickly. For example,
349 + 943 = 1292,
1292 + 2921 = 4213
4213 + 3124 = 7337
That is, 349 took three iterations to arrive at a palindrome.
Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome.
A number that never forms a palindrome through the reverse and add process is called a Lychrel number.
Due to the theoretical nature of these numbers, and for the purpose of this problem,
we shall assume that a number is Lychrel until proven otherwise.
In addition you are given that for every number below ten-thousand, it will either
(i) become a palindrome in less than fifty iterations, or,
(ii) no one, with all the computing power that exists, has managed so far to map it to a palindrome.
In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome:
4668731596684224866951378664 (53 iterations, 28-digits).
Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.
How many Lychrel numbers are there below ten-thousand?
NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.
*/
//249
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

const int upperlimit = 10000;

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
	vector<int> v;
};

void reverse(vector<int>& v)
{
	int i = 0;
	int j = v.size() - 1;
	while(j > i)
	{
		swap(v[i], v[j]);
		++i;
		--j;
	}
}

bool palindromic(BigInt x)
{
	int i = 0;
	int j = x.v.size() - 1;
	while(j > i)
	{
		if(x.v[i] != x.v[j])
		{
			return false;
		}
		++i;
		--j;
	}
	return true;
}

int PalindromeIterations(BigInt x)
{
	BigInt y1, y2;
	BigInt z;
	y1 = y2 = x;
	reverse(y2.v);
	z = y1 + y2;
	int i = 1;
	for(; !palindromic(z) && i < 50; ++i)
	{
		y1 = y2 = z;
		reverse(y2.v);
		z = y1 + y2;
	}
	if(i < 50)
	{
		return i;
	}
	else
	{
		return -1;
	}
}

int main()
{
	int cnt = 0;
	for(int ix = 1; ix < upperlimit; ++ix)
	{
		BigInt i;
		i = ix;
		if(PalindromeIterations(i) == -1)
		{
			cout << i << endl;
			++cnt;
		}
	}
	cout << cnt;

	return 0;
}