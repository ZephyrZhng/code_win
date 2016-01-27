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
NFA:
		0			1
q0		{q0, q3}	{q0, q1}
q1		phi			{q2}
q2		{q2}		{q2}
q3		{q4}		phi
q4		{q4}		{q4}
*/

class nfa
{
public:
	nfa();
	void init_nfa();
	void toDFA(vector< vector< set<string> > >& DFA);
	void display();
private:
	vector< vector< set<string> > > NFA;
};

void nfa::init_nfa()
{
	vector< set<string> > r0;
	set<string> s0;  s0.insert("q0");						r0.push_back(s0);
	set<string> s00; s00.insert("q0"); s00.insert("q3");	r0.push_back(s00);
	set<string> s01; s01.insert("q0"); s01.insert("q1");	r0.push_back(s01);
	vector< set<string> > r1;
	set<string> s1;  s1.insert("q1");						r1.push_back(s1);
	set<string> s10;										r1.push_back(s10);
	set<string> s11; s11.insert("q2");						r1.push_back(s11);
	vector< set<string> > r2;
	set<string> s2;  s2.insert("q2");						r2.push_back(s2);
	set<string> s20; s20.insert("q2");						r2.push_back(s20);
	set<string> s21; s21.insert("q2");						r2.push_back(s21);
	vector< set<string> > r3;
	set<string> s3;  s3.insert("q3");						r3.push_back(s3);
	set<string> s30; s30.insert("q4");						r3.push_back(s30);
	set<string> s31;										r3.push_back(s31);
	vector< set<string> > r4;
	set<string> s4;  s4.insert("q4");						r4.push_back(s4);
	set<string> s40; s40.insert("q4");						r4.push_back(s40);
	set<string> s41; s41.insert("q4");						r4.push_back(s41);
	NFA.push_back(r0);
	NFA.push_back(r1);
	NFA.push_back(r2);
	NFA.push_back(r3);
	NFA.push_back(r4);
}
nfa::nfa()
{
	ifstream NFAFile("E:\\document\\programs\\theory of computation\\NFA.txt");
	int K;
	int Sigma;
	NFAFile >> K >> Sigma;

	for(int i = 0; i < K; ++i)
	{
		vector< set<string> > r(Sigma + 1);
		NFA.push_back(r);
	}

	for(int i = 0; i < K; ++i)
	{
		string _q;
		NFAFile >> _q;
		NFA[i][0].insert(_q);

		bool flag = 1;
		// flag == 1: out of {...}
		// flag == 0: in the {...}

		for(int j = 1; j < Sigma + 1; )
		{
			string q;
			NFAFile >> q;
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
					NFA[i][j].insert(q);
				}
				if(flag == 1)
				{
					++j;
				}
			}
		}
	}

	NFAFile.close();
}

void nfa::display()
{
	for(int i = 0; i < NFA.size(); ++i)
	{
		for(int j = 0; j < NFA[i].size(); ++j)
		{
			cout << "(" << i << ", " << j << "): ";
			for(auto p = NFA[i][j].begin(); p != NFA[i][j].end(); ++p)
			{
				cout << *p << " ";
			}
			cout << endl;
		}
	}
}

void displayDFA(const vector< vector< set<string> > >& DFA)
{
	for(int i = 0; i < DFA.size(); ++i)
	{
		for(int j = 0; j < DFA[i].size(); ++j)
		{
			cout << "(" << i << ", " << j << "): ";
			for(auto p = DFA[i][j].begin(); p != DFA[i][j].end(); ++p)
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

void move(set<string>& dest, const set<string>& src)
{
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

int find(const vector< vector< set<string> > >& NFA, const string& q)
{
	for(int i = 0; i < NFA.size(); ++i)
	{
		if(*(NFA[i][0].begin()) == q)
		{
			return i;
		}
	}
}

void  nfa::toDFA(vector< vector< set<string> > >& DFA)
{
	int rowsize = NFA[0].size();
	set< set<string> > newlyAddedQueue;
	set< set<string> > record;
	vector< set<string> > _x(rowsize);
	move(_x[0], NFA[0][0]);
	DFA.push_back(_x);
	for(int i = 1; i < rowsize; ++i)
	{
		move(DFA[DFA.size() - 1][i], NFA[0][i]);
		newlyAddedQueue.insert(NFA[0][i]);
		record.insert(NFA[0][i]);
	}

	while(!newlyAddedQueue.empty())
	{
		set<string> newlyAdded(*(newlyAddedQueue.begin()));
		newlyAddedQueue.erase(newlyAddedQueue.begin());
		vector< set<string> > x(rowsize);
		move(x[0], newlyAdded);
		DFA.push_back(x);
		for(int i = 1; i < rowsize; ++i)
		{
			for(auto p = x[0].begin(); p != x[0].end(); ++p)
			{
				int rowLabel = find(NFA, *p);
				// DFA[DFA.size() - 1][i] <- NFA[rowLabel][i] or DFA[DFA.size() - 1][i]
				add(DFA[DFA.size() - 1][i], NFA[rowLabel][i]);
			}
			int oldRecordSize = record.size();
			record.insert(DFA[DFA.size() - 1][i]);
			if(oldRecordSize != record.size())
			{
				newlyAddedQueue.insert(DFA[DFA.size() - 1][i]);
			}
		}
	}
}

int main()
{
	nfa NFA;
	cout << "NFA:" << endl; NFA.display();

	cout << "-----------------------------" << endl;

	vector< vector< set<string> > > DFA;
	NFA.toDFA(DFA);
	cout << "DFA:" << endl; displayDFA(DFA);

	return 0;
}