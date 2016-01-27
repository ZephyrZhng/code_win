#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
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
#include <cassert>
#include <windows.h>

using namespace std;

/*
E_NFA:
	0		1		2		E
q0	{q0}	phi		phi		{q1}
q1	phi		{q1}	phi		{q2}
q2	phi		phi		{q2}	phi
*/

class e_nfa
{
public:
	e_nfa();
	void initE_NFA();
	void display();
	void E_CLOSURE(set<string>& E_CLOSURE_q, const string& q);
	void delta(const string& q, int a, set<string>& RLT);
	void toNFA(vector< vector< set<string> > >& NFA);
private:
	vector< vector< set<string> > > E_NFA;
};

void e_nfa::initE_NFA()
{
	// the last element of each row is related to E
	vector< set<string> > r0;
	set<string> s0;  s0.insert("q0");	r0.push_back(s0);
	set<string> s00; s00.insert("q0");	r0.push_back(s00);
	set<string> s01;					r0.push_back(s01);
	set<string> s02;					r0.push_back(s02);
	set<string> s0e; s0e.insert("q1");	r0.push_back(s0e);
	vector< set<string> > r1;
	set<string> s1;  s1.insert("q1");	r1.push_back(s1);
	set<string> s10;					r1.push_back(s10);
	set<string> s11; s11.insert("q1");	r1.push_back(s11);
	set<string> s12;					r1.push_back(s12);
	set<string> s1e; s1e.insert("q2");	r1.push_back(s1e);
	vector< set<string> > r2;
	set<string> s2;  s2.insert("q2");	r2.push_back(s2);
	set<string> s20; 					r2.push_back(s20);
	set<string> s21; 					r2.push_back(s21);
	set<string> s22; s22.insert("q2");	r2.push_back(s22);
	set<string> s2e; 					r2.push_back(s2e);

	E_NFA.push_back(r0);
	E_NFA.push_back(r1);
	E_NFA.push_back(r2);
}

e_nfa::e_nfa()
{
	ifstream E_NFAFile("E:\\document\\programs\\theory of computation\\E_NFA.txt");
	int K;
	int Sigma;
	E_NFAFile >> K >> Sigma;

	for(int i = 0; i < K; ++i)
	{
		vector< set<string> > r(Sigma + 2);
		E_NFA.push_back(r);
	}

	for(int i = 0; i < K; ++i)
	{
		string _q;
		E_NFAFile >> _q;
		E_NFA[i][0].insert(_q);

		bool flag = 1;
		// flag == 1: out of {...}
		// flag == 0: in the {...}

		for(int j = 1; j < Sigma + 2; )
		{
			string q;
			E_NFAFile >> q;
			if(q == "{")
			{
				flag = 0;
			}
			else if(q == "}")
			{
				flag = 1;
				++j;
			}
			else
			{
				if(q != "phi")
				{
					E_NFA[i][j].insert(q);
				}
				if(flag == 1)
				{
					++j;
				}
			}
		}
	}

	E_NFAFile.close();
}

void e_nfa::display()
{
	for(int i = 0; i < E_NFA.size(); ++i)
	{
		for(int j = 0; j < E_NFA[i].size(); ++j)
		{
			cout << "(" << i << ", ";
			if(j == E_NFA.size() - 1)
			{
				cout << "e): "; 
			}
			else
			{
				cout << j << "): ";
			}
			for(auto p = E_NFA[i][j].begin(); p != E_NFA[i][j].end(); ++p)
			{
				cout << *p << " ";
			}
			cout << endl;
		}
	}
}

void displayNFA(const vector< vector< set<string> > >& FA)
{
	for(int i = 0; i < FA.size(); ++i)
	{
		for(int j = 0; j < FA[i].size(); ++j)
		{
			cout << "(" << i << ", " << j << "): ";
			for(auto p = FA[i][j].begin(); p != FA[i][j].end(); ++p)
			{
				cout << *p << " ";
			}
			cout << endl;
		}
	}
}
void displaySet(const set<string>& s)
{
	for(auto p = s.begin(); p != s.end(); ++p)
	{
		cout << *p << " ";
	}
	cout << endl;
}

int find(const vector< vector< set<string> > >& E_NFA, const string& q)
{
	for(int i = 0; i < E_NFA.size(); ++i)
	{
		if(*(E_NFA[i][0].begin()) == q)
		{
			return i;
		}
	}
}

void replace(set<string>& dest, const set<string>& src)
{
	dest.clear();
	for(auto p = src.begin(); p != src.end(); ++p)
	{
		dest.insert(*p);
	}
}

void add(set<string>& A, const set<string>& B)
{
	for(auto p = B.begin(); p != B.end(); ++p)
	{
		A.insert(*p);
	}
}

bool equal(const set<string>& A, const set<string>& B)
{
	if(A.size() != B.size())
	{
		return false;
	}
	auto p = A.begin();
	auto q = B.begin();
	for(; p != A.end(); ++p, ++q)
	{
		if(*p != *q)
		{
			return false;
		}
	}
	return true;
}

void e_nfa::E_CLOSURE(set<string>& E_CLOSURE_q, const string& q)
{
	int _rowLabel = find(E_NFA, q);
	set<string> NEW_E_CLOSURE_q;
	set<string> OLD_E_CLOSURE_q(E_NFA[_rowLabel][E_NFA[_rowLabel].size() - 1]);
	if(E_NFA[_rowLabel][E_NFA[_rowLabel].size() - 1].empty())
	{
		OLD_E_CLOSURE_q.insert(q);
		replace(E_CLOSURE_q, OLD_E_CLOSURE_q);
		return;
	}
	while(!equal(NEW_E_CLOSURE_q, OLD_E_CLOSURE_q))
	{
		replace(NEW_E_CLOSURE_q, OLD_E_CLOSURE_q);
		for(auto p = OLD_E_CLOSURE_q.begin(); p != OLD_E_CLOSURE_q.end(); ++p)
		{
			int rowLabel = find(E_NFA, *p);
			add(NEW_E_CLOSURE_q, E_NFA[rowLabel][E_NFA[rowLabel].size() - 1]);
		}
		replace(OLD_E_CLOSURE_q, NEW_E_CLOSURE_q);
	}
	NEW_E_CLOSURE_q.insert(q);
	replace(E_CLOSURE_q, NEW_E_CLOSURE_q);
}

void e_nfa::delta(const string& q, int a, set<string>& RLT)
{
	set<string> E_CLOSURE_q;
	E_CLOSURE(E_CLOSURE_q, q);
	set<string> s;
	for(auto p = E_CLOSURE_q.begin(); p != E_CLOSURE_q.end(); ++p)
	{
		int rowLabel = find(E_NFA, *p);
		add(s, E_NFA[rowLabel][a + 1]);
	}
	for(auto p = s.begin(); p != s.end(); ++p)
	{
		set<string> tmpSet;
		E_CLOSURE(tmpSet, *p);
		add(RLT, tmpSet);
	}
}

void e_nfa::toNFA(vector< vector< set<string> > >& NFA)
{
	int rowSize = E_NFA[0].size() - 1;
	for(int i = 0; i < E_NFA.size(); ++i)
	{
		vector< set<string> > r(rowSize);
		NFA.push_back(r);
	}

	for(int i = 0; i < NFA.size(); ++i)
	{
		replace(NFA[i][0], E_NFA[i][0]);
	}

	for(int i = 0; i < E_NFA.size(); ++i)
	{
		for(int j = 1; j < E_NFA[i].size() - 1; ++j)
		{
			delta(*(E_NFA[i][0].begin()), j - 1, NFA[i][j]);
		}
	}
}

int main()
{
	e_nfa E_NFA;
	cout << "E_NFA:" << endl; E_NFA.display();

	cout << "-------------------------------" << endl;

	vector< vector< set<string> > > NFA;
	E_NFA.toNFA(NFA);
	cout << "NFA:" << endl; displayNFA(NFA);

	return 0;
}