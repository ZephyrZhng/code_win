#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

const int right = 1;
const int down  = 2;
const int left  = 3;
const int up    = 4;

typedef struct
{
	bool PassFlag;
	bool PathFlag;
}MElemType;

typedef struct
{
	int x;
	int y;
}PosType;

typedef struct
{
	int ord;
	PosType seat;
	int di;
}SElemType;

void display(const vector<SElemType>& s)
{
	for(int i = 0; i < s.size(); ++i)
		cout << "(" << s[i].seat.x << "," << s[i].seat.y << ") ";
	cout << endl;
}

void display(const vector<MElemType>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i].PassFlag << "\t";
	cout << endl;
}

void display(const vector< vector<MElemType> >& m)
{
	for(int i = 0; i < m.size(); ++i)
		display(m[i]);
}

inline bool equal(const PosType& p1, const PosType& p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

bool Pass(const PosType& p, const vector<SElemType>& s, const vector< vector<MElemType> >& maze)
{
	bool flag1 = true;
	for(int i = 0; i < s.size(); ++i)
		if(equal(s[i].seat, p)) { flag1 = false; break; }
	bool flag2 = maze[p.x][p.y].PassFlag && maze[p.x][p.y].PathFlag;
	return flag1 && flag2;
}

inline void FootPrint(const PosType& p, vector< vector<MElemType> >& maze)
{
	maze[p.x][p.y].PathFlag = false;
}

PosType NextPos(PosType& p, int di)
{
	switch(di)
	{
		case 1: return {p.x + 1, p.y};
		case 2: return {p.x, p.y + 1};
		case 3: return {p.x - 1, p.y};
		case 4: return {p.x, p.y - 1};
	}
}

void MazePath(vector< vector<MElemType> >& maze, const PosType& start, const PosType& end)
{
	vector<SElemType> s;
	PosType curpos = start;
	int curstep = 1;
	do
	{
		if(Pass(curpos, s, maze))
		{
			FootPrint(curpos, maze);
			SElemType e = {curstep, curpos, 1};
			s.push_back(e);
			if(equal(curpos, end)) break;
			curpos = NextPos(curpos, 1);
			++curstep;
		}
		else
		{
			if(!s.empty())
			{
				SElemType e = s[s.size() - 1];
				s.erase(s.end() - 1);
				while(e.di == 4 && !s.empty())
				{
					FootPrint(e.seat, maze);
					e = s[s.size() - 1];
					s.erase(s.end() - 1);
				}
				if(e.di < 4)
				{
					++e.di;
					s.push_back(e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	}while(!s.empty());

	display(s);
}

int main()
{
	vector< vector<MElemType> > maze;

	ifstream f("E:\\重要文档\\programs\\data structure\\3 栈和队列\\maze.txt");
	if(!f)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	int row, col;
	f >> row >> col;
	cout << row << " " << col << endl;
	for(int i = 0; i < row; ++i)
	{
		vector<MElemType> vi;
		maze.push_back(vi);
		for(int j = 0; j < col; ++j)
		{
			MElemType e;
			f >> e.PassFlag;
			e.PathFlag = true;
			maze[i].push_back(e);
		}
	}
	f.close();

	display(maze);
	MazePath(maze, {1, 1}, {8, 8});

	return 0;
}