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
using namespace std;

typedef struct arc
{
	int adjvex;
	struct arc *nextarc;
	int weight;
}arc;

typedef struct vex
{
	char data;
	arc *firstarc;
}vex;

int locate_vex(const vector<vex>& v, char x)
{
	for(int i = 0; i < v.size(); ++i)
		if(v[i].data == x) return i;
	return -1;
}

char v(const vector<vex>& v, int i)
{
	return v[i].data;
}

typedef struct node
{
	int data;
	struct node *pre, *next;
}node;

class my_queue
{
public:
	my_queue();
	~my_queue();
	void push(int i);
	void pop();
	int GetFrontData();
	int GetRearData();
	bool empty();
	node* GetHead();
	node* GetTail();
private:
	node *head, *tail;//真实的
	node *front, *rear;//对外的
};

my_queue::my_queue()
{
	front       = rear = head = tail = new node;
	front->next = rear->next = head->next = tail->next = NULL;
}

my_queue::~my_queue()
{
	for(node* p = head; p; )
	{
		node* temp = p;
		p          = p->next;
		delete temp;
	}
}

void my_queue::push(int i)
{
	node* p    = new node;
	p->data    = i;
	p->next    = NULL;
	p->pre     = front;
	rear->next = tail->next = p;
	rear       = tail = p;
}

void my_queue::pop()
{
	front = front->next;
}

int my_queue::GetFrontData()
{
	if(!front->next)
	{
		cerr << "队列空！" << endl;
		exit(0);
	}
	return front->next->data;
}

int my_queue::GetRearData()
{
	return rear->data;
}

bool my_queue::empty()
{
	return !front->next;
}

node* my_queue::GetHead()
{
	return head;
}

node* my_queue::GetTail()
{
	return tail;
}

class ALGraph//无向图的邻接表
{
public:
	ALGraph();
	~ALGraph();
	friend ostream& operator <<(ostream& output, const ALGraph& g);
	int FirstAdjVex(int v);
	int NextAdjVex(int v, int w);
	void BFS();
	void DFS();
	void SimplePath(int x, int y, vector<int>& path);
	void ShortestPath(char x, char y, vector<int>& p);
	void TopologicalSort();
	void TopologicalSort(stack<int>& t, vector<int>& ve);
	void CriticalPath();
	void Kruskal();
	bool Trans();
	void GetVexList(vector<vex>& v);
	int GetVexNum();
	int GetArcNum();
	void ArticulationPoint();
private:
	vector<vex> AdjList;
	int vexnum, arcnum;
	int kind;//0；无向图；1；有向图。
};

ALGraph::ALGraph()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\7 图\\adj list.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	input >> kind >> vexnum >> arcnum; cout << vexnum << "\t" << arcnum << endl;

	for(int i = 0; i < vexnum; ++i)
	{
		char data;
		input >> data;
		vex v = {data, NULL};
		AdjList.push_back(v); cout << AdjList[i].data;
	} cout << endl;

	for(int i = 0; i < arcnum; ++i)
	{
		char a, b;
		int w;
		input >> a >> b >> w; cout << a << "\t" << b << "\t" << w << endl;
		int x               = locate_vex(AdjList, a);
		int y               = locate_vex(AdjList, b);
		arc a1              = {y, NULL, w};
		arc* p1             = new arc(a1);
		p1->nextarc         = AdjList[x].firstarc;
		AdjList[x].firstarc = p1;
		if(!kind)
		{
			arc a2              = {x, NULL, w};
			arc* p2             = new arc(a2);
			p2->nextarc         = AdjList[y].firstarc;
			AdjList[y].firstarc = p2;
		}
	}

	input.close();
}

ALGraph::~ALGraph()
{
	for(int i = 0; i < vexnum; ++i)
		for(arc* p = AdjList[i].firstarc; p; )
		{
			arc* temp = p;
			p         = p->nextarc;
			delete temp;
		}
}

ostream& operator <<(ostream& output, const ALGraph& g)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		for(arc* p = g.AdjList[i].firstarc; p; p = p->nextarc)
			output << g.AdjList[i].data << v(g.AdjList, p->adjvex) << p->weight << "\t";
		cout << endl;
	}
	return output;
}

int ALGraph::FirstAdjVex(int v)
{
	return AdjList[v].firstarc? AdjList[v].firstarc->adjvex: -1;
}

int ALGraph::NextAdjVex(int v, int w)
{
	arc* p;
	for(p = AdjList[v].firstarc; p && p->adjvex != w; p = p->nextarc);
	if(!p) return -1;
	return p->nextarc? p->nextarc->adjvex: -1;
}

void ALGraph::BFS()
{
	vector<bool> vtag(vexnum);
	for(int i = 0; i < vexnum; ++i) vtag[i] = false;

	queue<int> q;
	for(int i = 0; i < vexnum; ++i)
	{
		if(!vtag[i])
		{
			vtag[i] = true;
			cout << v(AdjList, i);
			q.push(i);
			while(!q.empty())
			{
				int j = q.front();
				q.pop();
				for(int k = FirstAdjVex(j); k >= 0; k = NextAdjVex(j, k))
					if(!vtag[k])
					{
						vtag[k] = true;
						cout << v(AdjList, k);
						q.push(k);
					}
			}
		}
	}
}

void dfs(ALGraph& g, int i, const vector<vex>& vexlist, vector<bool>& vtag)
{
	vtag[i] = true;
	cout << v(vexlist, i);
	for(int j = g.FirstAdjVex(i); j >= 0; j = g.NextAdjVex(i, j))
		if(!vtag[j]) dfs(g, j, vexlist, vtag);
}

void ALGraph::DFS()
{
	vector<bool> vtag;
	for(int i = 0; i < vexnum; ++i) vtag.push_back(false);

	vector<vex> vexlist;
	GetVexList(vexlist);

	for(int i = 0; i < vexnum; ++i)
		if(!vtag[i]) dfs(*this, i, vexlist, vtag);
}

void simple_path(int x, int y, vector<int>& path, vector<bool>& vtag, ALGraph& g, bool& found)
{
	vtag[x] = true;
	path.push_back(x);

	for(int w = g.FirstAdjVex(x); w >= 0 && !found; w = g.NextAdjVex(x, w))
		if(w == y)
		{
			found = true;
			path.push_back(w);
		}
		else if(!vtag[w]) simple_path(w, y, path, vtag, g, found);

	if(!found)
		for(int i = 0; i < path.size(); ++i)
			if(path[i] == x) { path.erase(path.begin() + i); break; }
}

void ALGraph::SimplePath(int x, int y, vector<int>& path)
{
	vector<bool> vtag;
	for(int i = 0; i < vexnum; ++i) vtag.push_back(false);

	bool found(false);
	simple_path(x, y, path, vtag, *this, found);
}

void ALGraph::ShortestPath(char x, char y, vector<int>& path)
{
	int start = locate_vex(AdjList, x);
	int end   = locate_vex(AdjList, y);

	vector<bool> vtag(vexnum);
	for(int i = 0; i < vexnum; ++i) vtag[i] = false;

	my_queue q;
	int i = start;
	for(int i = start; i < vexnum; ++i)
	{
		if(!vtag[i])
		{
			vtag[i] = true;
			q.push(i);
			while(!q.empty())
			{
				int j = q.GetFrontData();
				q.pop();
				for(int k = FirstAdjVex(j); k >= 0; k = NextAdjVex(j, k))
				{
					if(!vtag[k])
					{
						vtag[k] = true;
						q.push(k);
					}
					if(k == end) goto label;
				}
			}
		}
	}

	label:
	for(node* p = q.GetTail(); p != q.GetHead(); p = p->pre)
		path.insert(path.begin(), p->data);
	for(int i = 0; i < path.size(); ++i)
		cout << v(AdjList, path[i]);
}

class my_stack
{
public:
	my_stack(int x, int y);
	~my_stack(){}
	bool empty();
	void push(int i);
	void pop();
	int top();
	vector<int> s;
private:
	int _top;
};

my_stack::my_stack(int x, int y): _top(-1)
{
	for(int i = 0; i < x; ++i)
		s.push_back(y);
}

bool my_stack::empty()
{
	return _top == -1;
}

void my_stack::push(int i)
{
	s[i] = _top;
	_top = i;
}

void my_stack::pop()
{
	_top = s[_top];
}

int my_stack::top()
{
	return _top;
}

void ALGraph::TopologicalSort()
{
	my_stack indegree(vexnum, 0);
	for(int i = 0; i < vexnum; ++i)
		for(arc* p = AdjList[i].firstarc; p; p = p->nextarc)
			++indegree.s[p->adjvex];

	for(int i = 0; i < vexnum; ++i)
		if(!indegree.s[i]) indegree.push(i);

	int cnt = 0;
	vector<char> seq;
	while(!indegree.empty())
	{
		int i = indegree.top();
		indegree.pop();
		seq.push_back(v(AdjList, i));
		++cnt;
		for(arc* p = AdjList[i].firstarc; p; p = p->nextarc)
		{
			int k = p->adjvex;
			if(!(--indegree.s[k])) indegree.push(k);
		}
	}
	if(cnt < vexnum) cout << "not directed acyclic graph(DAG)" << endl;
	else
	{
		for(int i = 0; i < seq.size(); ++i)
			cout << seq[i];
	}
}

void ALGraph::TopologicalSort(stack<int>& t, vector<int>& ve)
{
	my_stack indegree(vexnum, 0);
	for(int i = 0; i < vexnum; ++i)
		for(arc* p = AdjList[i].firstarc; p; p = p->nextarc)
			++indegree.s[p->adjvex];

	for(int i = 0; i < vexnum; ++i)
		if(!indegree.s[i]) indegree.push(i);

	int cnt = 0;
	while(!indegree.empty())
	{
		int i = indegree.top();
		indegree.pop();
		t.push(i);
		++cnt;
		for(arc* p = AdjList[i].firstarc; p; p = p->nextarc)
		{
			int k = p->adjvex;
			if(!(--indegree.s[k])) indegree.push(k);
			if(ve[i] + p->weight > ve[k]) ve[k] = ve[i] + p->weight;
		}
	}
}

void ALGraph::CriticalPath()
{
	stack<int> t;
	vector<int> ve(vexnum, 0);
	TopologicalSort(t, ve);
	vector<int> vl(ve.size(), ve[ve.size() - 1]);
	set<int> path;
	int len(0);

	while(!t.empty())
	{
		int j;
		arc* p;
		for(j = t.top(), t.pop(), p = AdjList[j].firstarc; p; p = p->nextarc)
			if(vl[p->adjvex] - p->weight < vl[j])
				vl[j] = vl[p->adjvex] - p->weight;
	}

	for(int j = 0; j < vexnum; ++j)
		for(arc* p = AdjList[j].firstarc; p; p = p->nextarc)
		{
			int k  = p->adjvex;
			int ee = ve[j];
			int el = vl[k] - p->weight;
			if(ee == el)
			{
				len += p->weight;
				cout << v(AdjList, j) << v(AdjList, k) << "\t";
				path.insert(j);
				path.insert(k);
			}
		}

	/*for(set<int>::iterator it = path.begin(); it != path.end(); ++it)
		cout << *it << "\t";*/
	cout << len << "\t";
}

void Kruskal()
{

}

bool ALGraph::Trans()
{
	for(int x = 0; x < vexnum; ++x)
		for(arc* py = AdjList[x].firstarc; py; py = py->nextarc)
		{
			int y = py->adjvex;
			for(arc* pz = AdjList[y].firstarc; pz; pz = pz->nextarc)
			{
				int z = pz->adjvex;
				if(z == x) continue;
				bool tag = false;
				for(arc* p = AdjList[x].firstarc; p; p = p->nextarc)
					if(p->adjvex == z)
					{
						tag = true;
						break;
					}
				if(!tag) return false;
			}
		}
	return true;
}

void ALGraph::GetVexList(vector<vex>& v)
{
	for(int i = 0; i < vexnum; ++i)
	{
		vex n;
		n.data = AdjList[i].data;
		v.push_back(n);
	}
}

int ALGraph::GetVexNum()
{
	return vexnum;
}

int ALGraph::GetArcNum()
{
	return arcnum;
}

void dfs_articul(const vector<vex>& AdjList, vector<int>& visited, vector<int>& low, int v0, int& cnt, set<char>& vexcut)
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
			if(low[w] >= visited[v0]) vexcut.insert(AdjList[v0].data);
		}
		else if(visited[w] < Min) Min = visited[w];
	}
	low[v0] = Min;
}

void ALGraph::ArticulationPoint()
{
	vector<int> low(vexnum);
	int cnt = 1;
	vector<int> visited(vexnum);
	visited[0] = 1;
	set<char> vexcut;

	for(int i = 1; i < vexnum; ++i) visited[i] = 0;
	arc *p = AdjList[0].firstarc;
	int v = p->adjvex;
	dfs_articul(AdjList, visited, low, v, cnt, vexcut);
	if(cnt < vexnum)
	{
		vexcut.insert(AdjList[0].data);
		while(p->nextarc)
		{
			p = p->nextarc;
			v = p->adjvex;
			if(!visited[v]) dfs_articul(AdjList, visited, low, v, cnt, vexcut);
		}
	}

	for(auto p = vexcut.begin(); p != vexcut.end(); ++p) cout << *p;
}

int main()
{
	cout << "declaration:" << endl;
	ALGraph test;
	vector<vex> vexlist;
	test.GetVexList(vexlist);
	cout << "vexlist:\t";
	for(int i = 0; i < vexlist.size(); ++i)
		cout << vexlist[i].data;
	cout << endl;

	cout << "--------------------------------" << endl;
	cout << "print:" << endl << test << endl;
	cout << "--------------------------------" << endl;
	cout << "FirstAdjVex:\t" << test.FirstAdjVex(3) << endl;
	cout << "NextAdjVex:\t" << test.NextAdjVex(3, 1) << endl;
	cout << "BFS:\t"; test.BFS(); cout << endl;
	cout << "DFS:\t"; test.DFS(); cout << endl;

	vector<int> path;
	cout << "SimplePath:\t"; test.SimplePath(1, 8, path);
	for(int i = 0; i < path.size(); ++i)
		cout << v(vexlist, path[i]);
	cout << endl;

	path.clear();
	cout << "ShortestPath:\t"; test.ShortestPath('C', 'I', path); cout << endl;

	cout << "TopologicalSort:\t"; test.TopologicalSort(); cout << endl;
	cout << "CriticalPath:\t"; test.CriticalPath(); cout << endl;
	cout << "Trans:\t" << test.Trans() << endl;

	cout << "ArticulationPoint:\t"; test.ArticulationPoint(); cout << endl;

	cout << endl;

	return 0;
}