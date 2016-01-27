#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;

class MGraph
{
public:
	MGraph();
	~MGraph(){}
	int LocateVex(char x);
	char Vex(int i);
	friend ostream& operator <<(ostream& ouput, const MGraph& g);
	void MiniSpanTree_Prim(char u);
private:
	vector<char> vex;
	vector< vector<int> > arc;
	int vexnum, arcnum;;
};

MGraph::MGraph()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\7 图\\adj list.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	input >> vexnum >> arcnum;
	cout << vexnum << "\t" << arcnum << endl;
	for(int i = 0; i < vexnum; ++i)
	{
		char x;
		input >> x;
		vex.push_back(x);
		cout << vex[i];
	}
	cout << endl;

	for(int i = 0; i < vexnum; ++i)
	{
		vector<int> ai;
		for(int i = 0; i < vexnum; ++i)
			ai.push_back(-1);
		arc.push_back(ai);
	}

	for(int i = 0; i < arcnum; ++i)
	{
		char v, w;
		int weight;
		input >> v >> w >> weight;
		int x = LocateVex(v);
		int y = LocateVex(w);

		arc[x][y] = arc[y][x] = weight;
	}

	input.close();
}

int MGraph::LocateVex(char x)
{
	for(int i = 0; i < vexnum; ++i)
		if(vex[i] == x) return i;
	return -1;
}

char MGraph::Vex(int i)
{
	return vex[i];
}

ostream& operator <<(ostream& output, const MGraph& g)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		for(int j = 0; j < g.vexnum; ++j)
			output << g.arc[i][j] << "\t";
		output << endl;
	}
	return output;
}

typedef struct node
{
	int adjvex;//-1：无关联；非负：关联节点的编号。
	int lowcost;//-1：未被查访；-2：已被查访；正数：权值。
}node;

void display(const vector<node>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << '(' << v[i].adjvex << ',' << v[i].lowcost << ')' << "\t";
	cout << endl;
}

void MGraph::MiniSpanTree_Prim(char u)
{
	vector<node> closedge(vexnum);
	int k = LocateVex(u);
	for(int j = 0; j < vexnum; ++j)
		if(arc[k][j] > 0) closedge[j] = {k, arc[k][j]};
		else closedge[j] = {-1, -1};
	closedge[k].lowcost = -2;
	//display(closedge); cout << "------------------------" << endl;

	for(int i = 1; i < vexnum; ++i)
	{
		int min(-1);
		for(int j = 0; j < vexnum; ++j)
			if(closedge[j].lowcost > 0)
			{
				min = closedge[j].lowcost;
				k   = j;
				break;
			}
		//cout << k << "\t" << min << endl;
		for(int j = 0; j < vexnum; ++j)
			if(closedge[j].lowcost > 0 && closedge[j].lowcost < min)
			{
				min = closedge[j].lowcost;
				k   = j;
			}
		//cout << k << "\t" << min << endl;

		cout << Vex(closedge[k].adjvex) << Vex(k) << endl;
		closedge[k].lowcost = -2;

		for(int j = 0; j < vexnum; ++j)
			if((closedge[j].lowcost == -1 && arc[k][j] != -1) ||
				(closedge[j].lowcost > 0 && arc[k][j] != -1 && arc[k][j] < closedge[j].lowcost))
			{
				closedge[j].adjvex  = k;
				closedge[j].lowcost = arc[k][j];
			}
		//display(closedge); cout << "><><><><><><><><><><><><><><>><><" <<endl;
	}
}

int main()
{
	MGraph g;

	cout << endl << g << endl;
	g.MiniSpanTree_Prim('A');

	return 0;
}