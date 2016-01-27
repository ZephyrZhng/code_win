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

typedef struct edge
{
	bool mark;
	int ivex, jvex;
	struct edge *ilink, *jlink;
	int weight;
}edge;

typedef struct vex
{
	char data;
	edge *firstedge;
}vex;

class AMLGraph
{
public:
	AMLGraph();
	~AMLGraph();
	int LocateVex(char x);
	friend ostream& operator <<(ostream& ouput, AMLGraph& g);
	int GetVexnum();
	int GetEdgenum();
private:
	vector<vex> adjmulist;
	vector<edge*> node;
	int vexnum, edgenum;
};

AMLGraph::AMLGraph()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\7 图\\adj list.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	input >> vexnum >> edgenum;
	cout << vexnum << "\t" << edgenum << endl;
	for(int i = 0; i < vexnum; ++i)
	{
		vex v;
		input >> v.data;
		v.firstedge = NULL;
		adjmulist.push_back(v);
		cout << adjmulist[i].data;
	}
	cout << endl;

	for(int i = 0; i < edgenum; ++i)
	{
		edge* p                = new edge;
		p->mark                = false;
		node.push_back(p);

		char v, w;
		input >> v >> w >> p->weight;
		cout << v << "\t" << w << "\t" << p->weight << endl;
		int x                  = LocateVex(v);
		int y                  = LocateVex(w);
		p->ivex                = x;
		p->jvex                = y;

		p->ilink               = adjmulist[x].firstedge;
		adjmulist[x].firstedge = p;
		p->jlink               = adjmulist[y].firstedge;
		adjmulist[y].firstedge = p;
	}

	input.close();
}

AMLGraph::~AMLGraph()
{
	for(int i = 0; i < node.size(); ++i)
		delete node[i];
}

int AMLGraph::LocateVex(char x)
{
	for(int i = 0; i < adjmulist.size(); ++i)
		if(adjmulist[i].data == x) return i;
	return -1;
}

ostream& operator <<(ostream& output, AMLGraph& g)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		for(edge* p = g.adjmulist[i].firstedge; p; p = p->ilink)
			output << g.adjmulist[p->ivex].data << g.adjmulist[p->jvex].data << p->weight << "\t";
		output << endl;
	}
	return output;
}

int AMLGraph::GetVexnum()
{
	return vexnum;
}

int AMLGraph::GetEdgenum()
{
	return edgenum;
}

int main()
{
	AMLGraph g;

	cout << endl << g << endl;

	return 0;
}