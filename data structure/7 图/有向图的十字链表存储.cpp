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

typedef struct InfoType
{
	int weight;
}InfoType;

typedef struct ArcBox
{
	int tailvex, headvex;
	InfoType info;
	struct ArcBox *hlink, *tlink;
}ArcBox;

typedef struct VexNode
{
	char data;
	ArcBox *firstin, *firstout;
}VexNode;

int locate_v(char x, const vector<VexNode>& v)
{
	for(int i = 0; i < v.size(); ++i)
		if(v[i].data == x) return i;
	return -1;
}

char v(int i, const vector<VexNode>& g)
{
	return g[i].data;
}

class OLGraph
{
public:
	OLGraph();
	~OLGraph();
	friend ostream& operator <<(ostream& output, const OLGraph& g);
	int LocateVex(char x){return locate_v(x, xlist);}
	void Dir();//按列输出十字链表
private:
	vector<VexNode> xlist;
	int vexnum, arcnum;
};

OLGraph::OLGraph()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\7 图\\graph.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	input >> vexnum >> arcnum;
	xlist.resize(vexnum);

	for(int i = 0; i < xlist.size(); ++i)
	{
		input >> xlist[i].data;
		xlist[i].firstin = xlist[i].firstout = NULL;
	}

	for(int i = 0; i < arcnum; ++i)
	{
		ArcBox* arc                 = new ArcBox;
		char v, w;
		input >> v >> w >> arc->info.weight;
		arc->tailvex                = locate_v(v, xlist);
		arc->headvex                = locate_v(w, xlist);
		arc->hlink                  = xlist[arc->headvex].firstin;
		arc->tlink                  = xlist[arc->tailvex].firstout;
		xlist[arc->headvex].firstin = xlist[arc->tailvex].firstout = arc;
	}

	input.close();
}

OLGraph::~OLGraph()
{
	for(int i = 0; i < vexnum; ++i)
		for(ArcBox* p = xlist[i].firstout; p; )
		{
			p            = p->tlink;
			ArcBox* temp = p;
			delete temp;
		}
}

ostream& operator <<(ostream& output, const OLGraph& g)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		for(ArcBox* p = g.xlist[i].firstout; p; p = p->tlink)
			output << v(p->tailvex, g.xlist) << v(p->headvex, g.xlist) << "\t";
		output << endl;
	}
	return output;
}

void OLGraph::Dir()
{
	for(int i = 0; i < vexnum; ++i)
	{
		for(ArcBox* p = xlist[i].firstin; p; p = p->hlink)
			cout << v(p->tailvex, xlist) << v(p->headvex, xlist) << "\t";
		cout << endl;
	}
}

int main()
{
	OLGraph test;

	cout << test << endl;
	test.Dir();

	return 0;
}