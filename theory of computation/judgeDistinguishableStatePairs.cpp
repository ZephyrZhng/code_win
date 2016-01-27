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

using namespace std;

class M
{
public:
	M();
	void display();

	vector<string>				K;
	vector<string>				Sigma;
	vector< vector<string> >	delta;
	string						q0;
	vector<string>				F;
};

M::M()
{
	ifstream MFile("E:\\document\\programs\\theory of computation\\DFA.txt");

	int k;
	int sigma;
	int f;

	MFile >> k;
	K.resize(k);
	for(int i = 0; i < k; ++i)
	{
		MFile >> K[i];
	}

	MFile >> sigma;
	Sigma.resize(sigma);
	for(int i = 0; i < sigma; ++i)
	{
		MFile >> Sigma[i];
	}

	delta.resize(k);
	for(int i = 0; i < k; ++i)
	{
		delta[i].resize(sigma);
		for(int j = 0; j < sigma; ++j)
		{
			MFile >> delta[i][j];
		}
	}

	MFile >> q0;

	MFile >> f;
	F.resize(f);
	for(int i = 0; i < f; ++i)
	{
		MFile >> F[i];
	}

	MFile.close();
}

void M::display()
{
	for(int i = 0; i < delta.size(); ++i)
	{
		for(auto& p: delta[i])
		{
			cout << p << "\t";
		}
		cout << endl;
	}
}

typedef struct grid
{
	bool cross;
	vector< pair<string, string> > statePairs;
}grid;

void displayTable(const vector< vector<grid> >& table)
{
	for(int i = 0; i < table.size(); ++i)
	{
		for(int j = 0; j < table[i].size(); ++j)
		{
			cout << (table[i][j].cross? 'x': '_') << "\t";
		}
		cout << endl;
	}
}

bool check(string p, string q, const vector< vector<grid> >& table, M DFA)
{
	for(int i = 0; i < DFA.Sigma.size(); ++i)
	{
		int		pPos          = find(DFA.K.begin(), DFA.K.end(), p) - DFA.K.begin();
		int		qPos          = find(DFA.K.begin(), DFA.K.end(), q) - DFA.K.begin();
		string	delta_p_a     = DFA.delta[pPos][i];
		string	delta_q_a     = DFA.delta[qPos][i];
		int		delta_p_a_Pos = find(DFA.K.begin(), DFA.K.end(), delta_p_a) - DFA.K.begin();
		int		delta_q_a_Pos = find(DFA.K.begin(), DFA.K.end(), delta_q_a) - DFA.K.begin();
		int		x             = ((delta_p_a_Pos > delta_q_a_Pos)? delta_p_a_Pos: delta_q_a_Pos) - 1;
		int		y             =  (delta_p_a_Pos < delta_q_a_Pos)? delta_p_a_Pos: delta_q_a_Pos;
		if(x + 1 != y && table[x][y].cross)
		{
			return true;
		}
	}

	return false;
}

void recurse(int x, int y, vector< vector<grid> >& table, M DFA)
{
	table[x][y].cross = true;
	if(!table[x][y].statePairs.empty())
	{
		while(!table[x][y].statePairs.empty())
		{
			int firstPos  = find(DFA.K.begin(), DFA.K.end(), table[x][y].statePairs[0].first ) - DFA.K.begin();
			int secondPos = find(DFA.K.begin(), DFA.K.end(), table[x][y].statePairs[0].second) - DFA.K.begin();
			int _x        = ((firstPos > secondPos)? firstPos: secondPos) - 1;
			int _y        =  (firstPos < secondPos)? firstPos: secondPos;
			// table[x][y].statePairs.erase(table[x][y].statePairs.begin());
			recurse(_x, _y, table, DFA);
		}
	}
}

void judgeDistinguishableStatePairs(vector< vector<grid> >& table, M DFA)
{
	for(int i = 0; i < DFA.K.size(); ++i)
	{
		for(int j = 0; j < DFA.K.size(); ++j)
		{
			if(find(DFA.F.begin(), DFA.F.end(), DFA.K[j]) == DFA.F.end() &&
			   find(DFA.F.begin(), DFA.F.end(), DFA.K[i]) != DFA.F.end())
			{
				int x = ((i > j)? i: j) - 1;
				int y =  (i < j)? i: j;
				table[x][y].cross = true;
			}
		}
	}

	for(int i = 0; i < table.size(); ++i)
	{
		for(int j = 0; j < table[i].size(); ++j)
		{
			string	p   = DFA.K[i + 1];
			string	q   = DFA.K[j];
			auto	_p  = find(DFA.F.begin(), DFA.F.end(), p);
			auto	_q  = find(DFA.F.begin(), DFA.F.end(), q);
			if(_p == DFA.F.end() && _q == DFA.F.end() ||
			   _p != DFA.F.end() && _q != DFA.F.end())
			{
				bool check_result = check(p, q, table, DFA);
				if(check_result)
				{
					recurse(i, j, table, DFA);
				}
				else
				{
					for(int k = 0; k < DFA.Sigma.size(); ++k)
					{
						string delta_p_a = DFA.delta[i + 1][k];
						string delta_q_a = DFA.delta[j    ][k];
						if(!(delta_p_a == delta_q_a ||
							 p == delta_p_a && q == delta_q_a ||
							 p == delta_q_a && q == delta_p_a))
						{
							int delta_p_a_Pos = find(DFA.K.begin(), DFA.K.end(), delta_p_a) - DFA.K.begin();
							int delta_q_a_Pos = find(DFA.K.begin(), DFA.K.end(), delta_q_a) - DFA.K.begin();
							int _x            = ((delta_p_a_Pos > delta_q_a_Pos)? delta_p_a_Pos: delta_q_a_Pos) - 1;
							int _y            =  (delta_p_a_Pos < delta_q_a_Pos)? delta_p_a_Pos: delta_q_a_Pos;

							bool flag = true;
							for(int cnt = 0; cnt < table[_x][_y].statePairs.size(); ++cnt)
							{
								if(table[_x][_y].statePairs[cnt].first  == p &&
								   table[_x][_y].statePairs[cnt].second == q ||
								   table[_x][_y].statePairs[cnt].first  == q &&
								   table[_x][_y].statePairs[cnt].second == p)
								{
									flag = false;
									break;
								}
							}
							if(flag &&
							   !(delta_p_a == p && delta_q_a == q ||
							   	 delta_p_a == q && delta_q_a == p))
							{
								table[_x][_y].statePairs.push_back(pair<string, string>(p, q));
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	M DFA;
	vector< vector<grid> > table;

	DFA.display();

	for(int i = 0; i < DFA.K.size() - 1; ++i)
	{
		table.push_back(vector<grid>(i + 1));
		for(int j = 0; j < table[i].size(); ++j)
		{
			table[i][j].cross = false;
		}
	}
	displayTable(table);

	judgeDistinguishableStatePairs(table, DFA);
	displayTable(table);

	return 0;
}