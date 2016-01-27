/*
The fraction 49/98 is a curious fraction, 
as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, 
which is correct, is obtained by cancelling the 9s.
We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
There are exactly four non-trivial examples of this type of fraction, less than one in value, 
and containing two digits in the numerator and denominator.
If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/
//100
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct fraction
{
	int numerator;
	int denominator;
};

inline bool equal(const struct fraction& a, const struct fraction& b)
{
	return (a.numerator == b.numerator && a.denominator == b.denominator);
}

inline int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

inline struct fraction simplify(int up, int down)
{
	int factor = gcd(up, down);
	fraction ans = {up / factor, down / factor};
	return ans;
}

inline bool trivial(int a, int b)
{
	return (!(a % 10) && !(b % 10));
}

inline void divide(int x, vector<int>& v)
{
	v.push_back(x / 10);
	v.push_back(x % 10);
}

int main()
{
	vector<struct fraction> ansv;
	for(int i = 10; i <= 99; ++i)
	{
		for(int j = i + 1; j <= 99; ++j)
		{
			if(!trivial(i, j))
			{
				vector<int> vi, vj;
				divide(i, vi);
				divide(j, vj);
				fraction frac = simplify(i, j);
				for(int pos = 0; pos < 2; ++pos)
				{
					vector<int>::iterator it = find(vj.begin(), vj.end(), vi[pos]);
					if(it != vj.end())
					{
						vi.erase(vi.begin() + pos);
						vj.erase(it);
						fraction fracprime = simplify(vi[0], vj[0]);
						if(equal(frac, fracprime))
						{
							ansv.push_back(frac);
						}
						break;
					}
				}
			}
		}
	}
	int ans(1), ansprime(1);
	for(int i = 0; i < ansv.size(); ++i)
	{
		ansprime *= ansv[i].numerator;
		ans *= ansv[i].denominator;
		cout << ansv[i].numerator << " / " << ansv[i].denominator << endl;
	}
	int fac = gcd(ans, ansprime);
	ans /= fac;
	cout << ans << endl;

	return 0;
}