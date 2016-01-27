#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;

typedef struct 
{
	long double coef;
	int 		expn;
}term, ElemType;

int BinSearch(const vector<ElemType>& v, int e)
{
	int low(0), mid(0), high(v.size() - 1);

	while(low <= high)
	{
		mid = (low + high) / 2;
		if(e > v[mid].expn)
			low = mid + 1;
		else if(e < v[mid].expn)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

class polynomial
{
public:
	polynomial(){}
	polynomial(const polynomial& P): p(P.p){}
	polynomial(const vector<ElemType>& v): p(v){}
	~polynomial(){}
	int length()
	{
		return p.size();
	}
	void sort()
	{
		for(int gap = p.size() / 2; gap > 0; gap /= 2)
			for(int i = gap; i < p.size(); ++i)
				for(int j = i - gap; j >= 0 && p[j].expn > p[j + gap].expn; j -= gap)
					swap(p[j], p[j + gap]);
	}
	friend inline ostream& operator <<(ostream& print, polynomial P)
	{
		for(int i = 0; i < P.p.size(); ++i)
			print << P.p[i].coef << "x^" << P.p[i].expn << " " << (i == P.p.size() - 1? "": "+ ");
		return print;
	}
	friend inline istream& operator >>(istream& create, polynomial& P)
	{
		int m;
		create >> m;
		for(int i = 0; i < m; ++i)
		{
			ElemType temp;
			create >> temp.coef >> temp.expn;
			P.p.push_back(temp);
		}
		return create;
	}
	friend polynomial operator +(const polynomial& p1, const polynomial& p2)
	{
		int i1(0), i2(0);
		polynomial P;
		for(; i1 < p1.p.size() && i2 < p2.p.size(); )
		{
			if(p1.p[i1].expn > p2.p[i2].expn)
			{
				P.p.push_back(p2.p[i2]);
				++i2;
				continue;
			}
			if(p1.p[i1].expn == p2.p[i2].expn)
			{
				term t = {p1.p[i1].coef + p2.p[i2].coef, p1.p[i1].expn};
				if(t.coef)
					P.p.push_back(t);
				++i1; ++i2;
				continue;
			}
			if(p1.p[i1].expn < p2.p[i2].expn)
			{
				P.p.push_back(p1.p[i1]);
				++i1;
				continue;
			}
		}
		if(i1 == p1.p.size() && i2 < p2.p.size())
		{
			P.p.insert(P.p.end(), p2.p.begin() + i2, p2.p.end());
			return P;
		}
		if(i2 == p2.p.size() && i1 < p1.p.size())
		{
			P.p.insert(P.p.end(), p1.p.begin() + i1, p1.p.end());
			return P;
		}
		return P;
	}
	friend polynomial operator +(const polynomial& P, const term& t)
	{
		polynomial ans(P);
		int i(0);

		for(; ans.p[i].expn < t.expn && i < ans.p.size(); ++i);
		if(i < ans.p.size() && ans.p[i].expn == t.expn)
		{
			ans.p[i].coef += t.coef;
			return ans;
		}
		if((i < ans.p.size() && ans.p[i].expn > t.expn) || i == ans.p.size())
		{
			ans.p.insert(ans.p.begin() + i, t);
			return ans;
		}
	}
	friend polynomial operator +(const polynomial& P, long double c)
	{
		polynomial ans(P);
		int i(0);
		for(; ans.p[i].expn <= 0; ++i)
			if(!ans.p[i].expn)
			{
				ans.p[i].coef += c;
				return ans;
			}
		term t = {c, 0};
		ans.p.insert(ans.p.begin() + i, t);
	}
	polynomial& operator =(const polynomial& P)
	{
		p = P.p;
		return *this;
	}
	polynomial& operator +=(const polynomial& P)
	{
		*this = *this + P;
		return *this;
	}
	polynomial& operator +=(const term& t)
	{
		*this = *this + t;
		return *this;
	}
	polynomial& operator +=(long double c)
	{
		*this = *this + c;
		return *this;
	}
	friend polynomial operator -(const polynomial& p1, const polynomial& p2)
	{
		polynomial minusp2(p2);
		for(int i = 0; i < minusp2.p.size(); ++i)
			minusp2.p[i].coef *= -1;
		polynomial P(p1 + minusp2);
		return P;
	}
	friend polynomial operator -(const polynomial& P, const term& t)
	{
		term minust = {-1 * t.coef, t.expn};
		polynomial ans(P + minust);
		return ans;
	}
	friend polynomial operator -(const polynomial& P, long double c)
	{
		term minuscx0 = {-1 * c, 0};
		polynomial ans(P + minuscx0);
		return ans;
	}
	polynomial& operator -=(const polynomial& P)
	{
		*this = *this - P;
		return *this;
	}
	polynomial& operator -=(const term& t)
	{
		*this = *this - t;
		return *this;
	}
	polynomial& operator -=(long double c)
	{
		*this = *this - c;
		return *this;
	}
	friend polynomial operator *(const polynomial& P, long double c)
	{
		polynomial ans(P);
		for(int i = 0; i < ans.p.size(); ++i)
			ans.p[i].coef *= c;
		return ans;
	}
	friend polynomial operator *(const polynomial& P, const term& t)
	{
		polynomial ans(P);
		for(int i = 0; i < ans.p.size(); ++i)
		{
			ans.p[i].coef *= t.coef;
			ans.p[i].expn += t.expn;
		}
		return ans;
	}
	friend polynomial operator *(const polynomial& p1, const polynomial& p2)
	{
		polynomial ans(p1 * p2.p[0]);
		for(int i = 1; i < p2.p.size(); ++i)
			ans += p1 * p2.p[i];
		return ans;
	}
	polynomial& operator *=(long double c)
	{
		*this = *this * c;
		return *this;
	}
	polynomial& operator *=(const term& t)
	{
		*this = *this * t;
		return *this;
	}
	polynomial& operator *=(const polynomial& P)
	{
		*this = *this * P;
		return *this;
	}
private:
	vector<ElemType> p;
};

int main()
{
	vector< vector<ElemType> > v;
	ifstream f("E:\\重要文档\\programs\\data structure\\2  线性表\\polyn.txt");
	if(!f)
	{
		cerr << "文件打开失败！" << endl;
		exit(0);
	}
	for(int i = 0; i < 2; ++i)
	{
		vector<ElemType> vi;
		v.push_back(vi);
		int n;
		f >> n;
		for(int j = 0; j < n; ++j)
		{
			ElemType temp;
			f >> temp.coef >> temp.expn;
			v[i].push_back(temp);
		}
	}
	polynomial p1(v[0]), p2(v[1]);
	
	cout << p1 << endl << p2 << endl;
	
	p1.sort(); p2.sort();
	cout << endl << p1 << endl << p2 << endl;
	/*
	polynomial test;
	cin >> test;
	cout << endl << test << endl;
	*/
	polynomial P;
	term t = {2, 3};
	/*
	P = p1 + p2;
	cout << endl << P << endl;
	P =  p1 + t;
	cout << endl << P << endl;
	P = p1 + 4;
	cout << endl << P << endl;
	P += p1;
	cout << endl << P << endl;
	P += t;
	cout << endl << P << endl;
	P += 5;
	cout << endl << P << endl;
	P = p1 - p2;
	cout << endl << P << endl;
	P =  p1 - t;
	cout << endl << P << endl;
	P = p1 - 4;
	cout << endl << P << endl;
	P -= p1;
	cout << endl << P << endl;
	P -= t;
	cout << endl << P << endl;
	P -= 5;
	cout << endl << P << endl;
	
	P = p1 * p2;
	cout << endl << P << endl << P.length() << endl;
	P = p1 * t;
	cout << endl << P << endl;
	P = p1 * 2;
	cout << endl << P << endl;
	P *= p2;
	cout << endl << P << endl;
	P *= t;
	cout << endl << P << endl;
	P *= 4;
	cout << endl << P << endl;
	*/

	return 0;
}