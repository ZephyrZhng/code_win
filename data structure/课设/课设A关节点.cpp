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

typedef struct arc
{
	int adjvex;
	struct arc *nextarc;
	int weight;
	bool del;
}arc;

typedef struct vex
{
	char data;
	string city;
	arc *firstarc;
	bool del;
}vex;

class cmp
{
public:
	bool operator ()(const vex& v1, const vex& v2) const
	{return v1.city < v2.city;}
};

class _cmp
{
public:
	bool operator ()(const set<string>& s1, const set<string>& s2) const
	{return *s1.begin() < *s2.begin();}
};

class Graph//无向图的邻接表
{
public:
	Graph();
	void AdjMatrixConstructor();
	~Graph();
	int locate_vex(char x) const;
	int FirstAdjVex(int v) const;
	int NextAdjVex(arc* p) const;
	void RemoveVex(int x);
	void RecoverVex(int x);
	friend ostream& operator <<(ostream& output, const Graph& g);
	void BFS();
	void DFS();
	//void ShortestPath(char x, char y, vector<int>& p);
	void ArticulationPoint();
	void QueryArticul();
	void TransArticul();
private:
	vector<vex> AdjList;
	vector<vex> AdjMatrixVex;
	vector< vector<int> > AdjMatrixArc;
	int vexnum, arcnum;
	int kind;//0；无向图；1；有向图。
	set<vex, cmp> vexcut;
	set< set<string>, _cmp > ConnectedComponent;//记录连通分量
};

Graph::Graph()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\课设\\A.txt");
	assert(input);

	input >> kind >> vexnum >> arcnum; //cout << vexnum << "\t" << arcnum << endl;

	for(int i = 0; i < vexnum; ++i)
	{
		vex v;
		input >> v.data >> v.city;
		v.firstarc = NULL;
		v.del = false;
		AdjList.push_back(v); //cout << AdjList[i].data;
	} //cout << endl;

	for(int i = 0; i < arcnum; ++i)
	{
		char a, b;
		int w;
		input >> a >> b >> w; //cout << a << "\t" << b << "\t" << w << endl;
		int x               = locate_vex(a);
		int y               = locate_vex(b);
		arc* p1             = new arc((arc){y, NULL, w, false});
		p1->nextarc         = AdjList[x].firstarc;
		AdjList[x].firstarc = p1;
		if(!kind)
		{
			arc* p2             = new arc((arc){x, NULL, w, false});
			p2->nextarc         = AdjList[y].firstarc;
			AdjList[y].firstarc = p2;
		}
	}

	input.close();
}

void Graph::AdjMatrixConstructor()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\7 图\\adj list.txt");
	assert(input);

	input >> kind >> vexnum >> arcnum;

	for(int i = 0; i < vexnum; ++i)
	{
		vex v;
		input >> v.data >> v.city;
		v.firstarc = NULL;
		v.del = false;
		AdjMatrixVex.push_back(v);
	}

	for(int i = 0; i < vexnum; ++i)
	{
		vector<int> AMAi;
		for(int i = 0; i < vexnum; ++i)
			AMAi.push_back(-1);
		AdjMatrixArc.push_back(AMAi);
	}

	for(int i = 0; i < arcnum; ++i)
	{
		char a, b;
		int w;
		input >> a >> b >> w;
		int x = locate_vex(a);
		int y = locate_vex(b);
		AdjMatrixArc[x][y] = AdjMatrixArc[y][x] = w;
	}

	input.close();
}

Graph::~Graph()
{
	for(int i = 0; i < vexnum; ++i)
		for(arc* p = AdjList[i].firstarc; p; )
		{
			arc* temp = p;
			p         = p->nextarc;
			delete temp;
		}
}

inline int Graph::locate_vex(char x) const
{
	return (x - 'A' >= vexnum)? -1: x - 'A';
}

inline int Graph::FirstAdjVex(int v) const
{
	return AdjList[v].firstarc? AdjList[v].firstarc->adjvex: -1;
}

inline int Graph::NextAdjVex(arc* p) const
{
	return p->nextarc? p->nextarc->adjvex: -1;
}

void Graph::RemoveVex(int i)
{
	AdjList[i].del = true;
	for(arc *p = AdjList[i].firstarc; p; p = p->nextarc)
		for(arc *q = AdjList[p->adjvex].firstarc; q; q = q->nextarc)
			if(q->adjvex == i)
			{
				q->del = true; break;
			}
}

void Graph::RecoverVex(int i)
{
	AdjList[i].del = false;
	for(arc *p = AdjList[i].firstarc; p; p = p->nextarc)
		for(arc *q = AdjList[p->adjvex].firstarc; q; q = q->nextarc)
			if(q->adjvex == i)
			{
				q->del = false; break;
			}
}

ostream& operator <<(ostream& output, const Graph& g)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		for(arc* p = g.AdjList[i].firstarc; p; p = p->nextarc)
			output << g.AdjList[i].city << " " << g.AdjList[p->adjvex].city << " " << p->weight << "\t";
		cout << endl;
	}
	return output;
}

void Graph::BFS()
{
	vector<int> vtag(vexnum);
	for(int i = 0; i < vexnum; ++i) vtag[i] = false;

	queue<int> q;
	int cnt(1);
	for(int i = 0; i < vexnum; ++i)
		if(!vtag[i])
		{
			cout << cnt << ":"; ++cnt;
			vtag[i] = true;
			cout << AdjList[i].city << " ";
			q.push(i);
			while(!q.empty())
			{
				int j = q.front();
				q.pop();
				arc* p = AdjList[j].firstarc;
				int k = FirstAdjVex(j);
				for(; p && k >= 0; k = NextAdjVex(p), p = p->nextarc)
					if(!vtag[k])
					{
						vtag[k] = true;
						cout << AdjList[k].city << " ";
						q.push(k);
					}
			}
		}
}

void dfs(Graph& g, const vector<vex>& AdjList, int i, vector<int>& vtag, set<string>& si)
{
	vtag[i] = true;
	cout << AdjList[i].city << " ";
	si.insert(AdjList[i].city);
	arc* p = AdjList[i].firstarc;
	int j = g.FirstAdjVex(i);
	for(; p && j >= 0; j = g.NextAdjVex(p), p = p->nextarc)
		if(!vtag[j] && !p->del) dfs(g, AdjList, j, vtag, si);
}

void Graph::DFS()
{
	vector<int> vtag;
	ConnectedComponent.clear();
	int cnt(1);
	for(int i = 0; i < vexnum; ++i) vtag.push_back(false);
	for(int i = 0; i < vexnum; ++i)
		if(!vtag[i] && !AdjList[i].del)
		{
			cout << cnt << "."; ++cnt;
			set<string> si;
			dfs(*this, this->AdjList, i, vtag, si);
			ConnectedComponent.insert(si);
		}
}

void dfs_articul(vector<vex>& AdjList, vector<int>& visited, vector<int>& low,
	int v0, int& cnt, set<vex, cmp>& vexcut)
{
	visited[v0] = ++cnt;
	int Min = visited[v0];
	for(arc* p = AdjList[v0].firstarc; p; p = p->nextarc)
	{
		int w = p->adjvex;
		if(!visited[w])
		{
			dfs_articul(AdjList, visited, low, w, cnt, vexcut);
			if(low[w] < Min) Min = low[w];
			if(low[w] >= visited[v0])
				vexcut.insert((vex){'A' + v0, AdjList[v0].city, AdjList[v0].firstarc, false});
		}
		else if(visited[w] < Min) Min = visited[w];
	}
	low[v0] = Min;
}

void Graph::ArticulationPoint()
{
	vector<int> low(vexnum);
	int cnt = 1;
	vector<int> visited(vexnum);
	visited[0] = 1;

	for(int i = 1; i < vexnum; ++i) visited[i] = 0;
	arc *p = AdjList[0].firstarc;
	int v = p->adjvex;
	dfs_articul(AdjList, visited, low, v, cnt, vexcut);
	if(cnt < vexnum)
	{
		vexcut.insert((vex){'A' + 0, AdjList[0].city, AdjList[0].firstarc, false});
		while(p->nextarc)
		{
			p = p->nextarc;
			v = p->adjvex;
			if(!visited[v]) dfs_articul(AdjList, visited, low, v, cnt, vexcut);
		}
	}
	cout << "共有" << vexcut.size() << "个关节点：\t";
	for(auto p = vexcut.begin(); p != vexcut.end(); ++p) cout << p->city << " ";
}

void Graph::QueryArticul()
{
	cout << "╭(╯^╰)╮查询关节点" << endl;
	char ask('y');
	while(ask == 'y')
	{
		string querycity;
		cout << "输入要查询的城市：" << endl;
		cin >> querycity;
		bool tag = false;
		for(auto p = vexcut.begin(); p != vexcut.end(); ++p)
			if(p->city == querycity) {cout << "是关节点" << endl; tag = true; break;}
		if(!tag) cout << "不是关节点" << endl;
		cout << "是否继续查询？（请输入y（是）/n（否））\t";
		cin >> ask;
	}
}

void combination(vector< vector<string> >& v, int n, vector<string>& vtmp, vector< vector<string> >& tmp_result)
{
	for(int i = 0; i < v[n].size(); ++i)
	{
		vtmp.push_back(v[n][i]);
		if(n < v.size() - 1)
			combination(v, n + 1, vtmp, tmp_result);
		else
		{
			vector<string> one_result;
			for (int j = 0; j < vtmp.size(); ++j)
				one_result.push_back(vtmp[j]);
			tmp_result.push_back(one_result);
		}
		vtmp.pop_back();
	}
}

void Graph::TransArticul()
{
	for(auto p = vexcut.begin(); p != vexcut.end(); ++p)
	{
		cout << endl << "---------------------------------------------------------------" << endl;
		cout << "若删除" << p->city << "，连通分量为：" << endl;
		RemoveVex(p->data - 'A');
		DFS(); cout << endl;
		RecoverVex(p->data - 'A');

		cout << endl << "要想将" << p->city << "变为非关节点，需要在以下城市间修建铁路：" << endl;
		vector< vector<string> > vConnectedComponent;
		for(auto p = ConnectedComponent.begin(); p != ConnectedComponent.end(); ++p)
		{
			vector<string> vi;
			vConnectedComponent.push_back(vi);
			for(auto q = p->begin(); q != p->end(); ++q)
				vConnectedComponent[distance(ConnectedComponent.begin(), p)].push_back(*q);
		}

		vector< vector<string> > result;
		vector<string> vtmp;
		combination(vConnectedComponent, 0, vtmp, result);

		for(int i = 0; i < result.size(); ++i)
		{
			for(int j = 0; j < result[i].size(); ++j)
				cout << result[i][j] << " ";
			cout << "/";
		}
		cout << endl << "---------------------------------------------------------------" << endl;
	}
}

int main()
{
	Graph test;

	cout << "<<:" << endl << test;
	cout << "BFS:" << endl; test.BFS(); cout << endl;
	cout << "DFS:" << endl; test.DFS(); cout << endl;
	cout << "ArticulationPoint:" << endl; test.ArticulationPoint(); cout << endl;
	cout << "TransArticul:" << endl; test.TransArticul(); cout << endl;
	cout << "查询：" << endl; test.QueryArticul(); cout << endl;

	return 0;
}