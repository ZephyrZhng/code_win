#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
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
using namespace std;

typedef struct teacher_node
{
	char data;
	string teacher_name;
}teacher_node;

typedef struct course_node
{
	char data;
	string course_name;
}course_node;

class MGraph
{
public:
	MGraph();
	~MGraph(){}
	int locate_xvex(char x) const;
	int locate_yvex(char y) const;
	friend ostream& operator <<(ostream& ouput, const MGraph& g);
	int km(int x, vector<int>& vis, vector<int>& xlink, vector<int>& ylink);
	void Match();
private:
	vector<teacher_node> xvex;
	vector<course_node> yvex;
	vector< vector<int> > arc;
	vector<int> _arcnum;
	int vexnum, xnum, ynum, arcnum;
};

MGraph::MGraph()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\课设\\B.txt");
	assert(input);

	input >> vexnum >> xnum >> ynum >> arcnum;
	_arcnum.resize(xnum);
	cout << vexnum << "\t" << xnum << "\t" << ynum << "\t" << arcnum << endl;
	for(int i = 0; i < xnum; ++i)
	{
		teacher_node t;
		input >> t.data >> t.teacher_name;
		xvex.push_back(t);
		vector<int> ai(ynum, 0);
		arc.push_back(ai);
	}
	for(int i = 0; i < ynum; ++i)
	{
		course_node c;
		input >> c.data >> c.course_name;
		yvex.push_back(c);
	}

	for(int i = 0; i < xnum; ++i)
	{
		int n;
		char x, y;
		input >> x >> n;
		_arcnum[x - 'a'] = n;
		for(int i = 0; i < n; ++i)
		{
			input >> y;
			arc[x - 'a'][y - 'A'] = 1;
		}
	}

	input.close();
}

inline int MGraph::locate_xvex(char x) const
{
	return (x - 'a' >= xnum)? -1: x - 'a';
}

inline int MGraph::locate_yvex(char y) const
{
	return (y - 'A' >= ynum)? -1: y - 'A';
}

ostream& operator <<(ostream& output, const MGraph& g)
{
	for(int i = 0; i < g.xnum; ++i)
	{
		output << g.xvex[i].teacher_name << "可教的课：\t";
		for(int j = 0; j < g.ynum; ++j)
		{
			if(!g.arc[i][j]) continue;
			output << g.yvex[j].course_name << "\t";
		}
		output << endl;
	}
	return output;
}

int MGraph::km(int x, vector<int>& vis, vector<int>& xlink, vector<int>& ylink)
{
	for(int i = 0; i < ynum; ++i)
		if(arc[x][i] && !vis[i])
		{
			vis[i] = 1;
			if(ylink[i] == -1 || km(ylink[i], vis, xlink, ylink))
			{
				xlink[x] = i;
				ylink[i] = x;
				return 1;
			}
		}
	return 0;
}

void MGraph::Match()
{
	vector<int> vis(ynum, 0);
	vector<int> xlink(xnum, -1);
	vector<int> ylink(ynum, -1);
	for(int i = 0; i < xnum; ++i)
	{
		if(xlink[i] == -1)
		{
			fill(vis.begin(), vis.end(), 0);
			km(i, vis, xlink, ylink);
		}
	}
	for(int i = 0; i < xlink.size(); ++i)
		cout << xvex[i].teacher_name << "教" << yvex[xlink[i]].course_name << endl;
}

int main()
{
	MGraph g;

	cout << g << endl;
	g.Match(); cout << endl;

	return 0;
}