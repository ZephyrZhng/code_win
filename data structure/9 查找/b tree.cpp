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

void display(const vector<int>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << ' ';
	cout << endl;
}

typedef struct node
{
	struct node* parent;
	vector<int> key;
	vector<struct node*> ptr;
}node, *btree;

class Btree
{//查找和插入函数！！！！！！！！！！！！
public:
	Btree();
	~Btree();
	void InOrderTraverse();
private:
	btree root;
	int m, N;
};

Btree::Btree(): root(NULL)
{
	ifstream input("E:\\重要文档\\programs\\data structure\\9 查找\\b tree.txt");
	assert(input);
	input >> m >> N;

	int k;
	while(input >> k)
	{
		node *p    = root, *q = NULL;
		bool found = false;
		int i      = 0;

		while(p && !found)
		{
			for(i = 0; i < p->key.size() && p->key[i] < k; ++i);
			if(i < p->key.size() && p->key[i] == k) found = true;
			else { q = p; p = p->ptr[i]; }
		}
		if(found) continue;

		int x         = k;
		node *ap      = NULL;
		bool finished = false;

		while(q && !finished)
		{
			q->key.insert(q->key.begin() + i, x);
			q->ptr.insert(q->ptr.begin() + i + 1, ap);
			if(q->key.size() < m) { finished = true; continue; }

			int s      = m % 2? m / 2 + 1: m / 2;
			x          = q->key[s - 1];

			ap         = new node;
			ap->parent = q->parent;
			ap->key.resize(m - s);
			ap->ptr.resize(m - s + 1);
			copy(q->key.begin() + s, q->key.end(), ap->key.begin());
			copy(q->ptr.begin() + s, q->ptr.end(), ap->ptr.begin());

			int j1 = q->key.size() - s + 1;
			int j2 = q->ptr.size() - s;
			for(int j = 0; j < j1; ++j)
				q->key.erase(q->key.end() - 1);
			for(int j = 0; j < j2; ++j)
				q->ptr.erase(q->ptr.end() - 1);

			q = q->parent;
			if(q) for(i = 0; i < q->key.size() && q->key[i] < x; ++i);
		}

		if(!finished)
		{
			node* oldroot = root;
			root          = new node;
			root->key.push_back(x);
			root->ptr.push_back(oldroot);
			root->ptr.push_back(ap);
			root->parent  = NULL;
		}
	}

	input.close();
}

void destruct(node* t)
{
	if(t)
	{
		for(int i = 0; i < t->ptr.size(); ++i)
			destruct(t->ptr[i]);
		bool tag = true;
		for(int i = 0; i < t->ptr.size(); ++i)
			if(t->ptr[i]) { tag = false; break; }
		if(tag) delete t;
	}
}

Btree::~Btree()
{
	destruct(root);
}

void inordertraverse(node* t)
{
	if(t)
	{
		inordertraverse(t->ptr[0]);
		for(int i = 0; i < t->key.size(); ++i)
		{
			cout << t->key[i] << '\t';
			inordertraverse(t->ptr[i + 1]);
		}
	}
}

void Btree::InOrderTraverse()
{
	inordertraverse(root);
}

int main()
{
	Btree b;
	b.InOrderTraverse();
	return 0;
}