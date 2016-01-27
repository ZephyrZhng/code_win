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

const double eps = 1e-8;

class Frac
{
public:
	Frac() {}
	Frac(const Frac& _frac): num(_frac.num), den(_frac.den) {}
	Frac(long long _num, long long _den): num(_num), den(_den) {}

	Frac& operator =(const Frac& frac)
	{
		num = frac.num;
		den = frac.den;
		return *this;
	}

	long long num;
	long long den;
};

class MixedFrac
{
public:
	MixedFrac() {}
	MixedFrac(const MixedFrac& _mixedFrac): integer(_mixedFrac.integer), num(_mixedFrac.num), den(_mixedFrac.den) {}
	MixedFrac(long long _integer, long long _num, long long _den): integer(_integer), num(_num), den(_den) {}

	MixedFrac& operator =(const MixedFrac& mixedFrac)
	{
		integer = mixedFrac.integer;
		num     = mixedFrac.num;
		den     = mixedFrac.den;
		return *this;
	}

	long long integer;	//带分数的整数部分
	long long num;		//分子
	long long den;		//分母
};

inline int sgn(double x)
{
	return (x) > 0 ? 1 : ((x) < 0 ? -1 : 0);
}

inline double fabs(double x)
{
	return (x) > 0 ? (x) : (-x);
}

inline int zero(double x)
{
	return (((x) > 0 ? (x) : (-x)) < eps);
}

inline long long gcd(long long a, long long b)
{
	return b ? gcd(b, a % b) : a;
}

inline long long lcm(long long a, long long b)
{
	return a * b / gcd(a, b);
}

class fraction
{
public:
	fraction() {}
	
	template<typename T>
	fraction(const T& _a): a(_a)
	{
		a    = fabs(_a);
		sign = (_a > 0)? 1: ((_a < 0)? -1: 0);
		convToFrac();
		convToMixedFrac();
	}

	fraction(const fraction& _frac): a(_frac.a), frac(_frac.frac), mixedFrac(_frac.mixedFrac), sign(_frac.sign)
	{
		simplify();
	}

	fraction(long long _num, long long _den): frac(Frac(abs(_num), abs(_den))),
								  mixedFrac(MixedFrac((long long)(abs(_num) / abs(_den)), abs(_num) % abs(_den), abs(_den))),
								  a(double(_num) / double(_den)),
								  sign(sgn(_num) * sgn(_den))
	{
		simplify();
	}

	fraction(long long _integer, long long _num, long long _den): frac(Frac(abs(_integer) * abs(_den) + abs(_num), abs(_den))),
												mixedFrac(MixedFrac(abs(_integer), abs(_num), abs(_den))),
												a(double(abs(_integer) * abs(_den) + abs(_num)) / double(abs(_den))),
												sign(sgn(_integer) * sgn(_num) * sgn(_den))
	{
		simplify();
	}

	void simplify()
	{
		long long gcd_num_den_frac      = gcd(frac.num, frac.den);
		frac.num                        /= gcd_num_den_frac;
		frac.den                        /= gcd_num_den_frac;
		long long gcd_num_den_mixedFrac = gcd(mixedFrac.num, mixedFrac.den);
		mixedFrac.num                   /= gcd_num_den_mixedFrac;
		mixedFrac.den                   /= gcd_num_den_mixedFrac;
	}

	void convToFrac()
	{
		long long dec, gcd_num_den;
		double x;

		if(!zero(fabs(a) - (long long)fabs(a)))
		{
			for(dec = 0, x = fabs(a); !zero(x - (long long)x); x *= 10, ++dec);
			frac.num    = fabs(a) * pow(10, dec);
			frac.den    = pow(10, dec);
			gcd_num_den = gcd(frac.num, frac.den);
			frac.num   /= gcd_num_den;
			frac.den   /= gcd_num_den;
		}
		else
		{
			frac.num = fabs(a);
			frac.den = 1;
		}
	}

	void convToMixedFrac()
	{
		convToFrac();
		mixedFrac.num     = frac.num;
		mixedFrac.den     = frac.den;
		mixedFrac.integer = 1;

		if((mixedFrac.num > mixedFrac.den) && (mixedFrac.den != 1))
		{
			mixedFrac.integer = (long long)(frac.num / frac.den);
			mixedFrac.num    -= mixedFrac.integer * mixedFrac.den;
		}
	}

	void outputFracForm()
	{
		cout << sign * frac.num << "/" << frac.den << endl;
	}

	void outputMixedFracForm()
	{
		cout << sign * mixedFrac.integer << " " ;
		cout << mixedFrac.num << "/" << mixedFrac.den << endl;
	}

	friend fraction operator +(const fraction& a, const fraction& b)
	{
		if(!a.sign) return b;
		if(!b.sign) return a;
		if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
		{
			long long lcm_den1_den2 = lcm(a.frac.den, b.frac.den);
			long long coefficient1  = lcm_den1_den2 / a.frac.den;
			long long coefficient2  = lcm_den1_den2 / b.frac.den;
			return fraction(a.sign * (a.frac.num * coefficient1 + b.frac.num * coefficient2), lcm_den1_den2);
		}
		if(a.sign == 1 && b.sign == -1 || a.sign == -1 && b.sign == 1)
		{
			long long lcm_den1_den2 = lcm(a.frac.den, b.frac.den);
			long long coefficient1  = lcm_den1_den2 / a.frac.den;
			long long coefficient2  = lcm_den1_den2 / b.frac.den;
			return fraction(
				(fabs(a.a) > fabs(b.a)? (a.sign == 1? 1: -1): (fabs(a.a) < fabs(b.a)? (a.sign == 1? -1: 1): 0))
				* (abs(a.frac.num * coefficient1 - b.frac.num * coefficient2)),
				lcm_den1_den2
			);
		}
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
		return a + (-1 * b);
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
		return fraction(a.sign * b.sign * a.frac.num * b.frac.num, a.frac.den * b.frac.den);
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
		return fraction(a.sign * b.sign * a.frac.num * b.frac.den, a.frac.den * b.frac.num);
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
		frac      = _a.frac;
		mixedFrac = _a.mixedFrac;
		a         = _a.a;
		sign      = _a.sign;
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
		if(sign > _a.sign) return false;
		if(sign < _a.sign) return true;
		long long lcm_den1_den2 = lcm(frac.den, _a.frac.den);
		long long  coefficient  = lcm_den1_den2 /    frac.den;
		long long _coefficient  = lcm_den1_den2 / _a.frac.den;
		bool judge        = frac.num * coefficient < _a.frac.num * _coefficient;
		if(sign == 1  && judge || sign == -1 && !judge) return true;
		return false;
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
			   a             == _a.a
			&& frac.num      == _a.frac.num      && frac.den      == _a.frac.den
			&& mixedFrac.num == _a.mixedFrac.num && mixedFrac.den == _a.mixedFrac.den
			&& sign          == _a.sign
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
		output << a.frac.num << " / " << a.frac.den;
		return output;
	}

	double		a;
	Frac 		frac;
	MixedFrac 	mixedFrac;
	int			sign;
};

int main()
{
	return 0;
}