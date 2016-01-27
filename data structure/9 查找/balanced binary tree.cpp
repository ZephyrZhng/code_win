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

typedef struct node
{
	int data;
	int bf;
	struct node *lchild, *rchild;
}node, *bbtree;

class Bbtree
{
public:
	Bbtree();
	~Bbtree();
	void Insert(int e);
	void Inordertraverse();
private:
	bbtree root;
};

void lrotate(node*& p)
{
	node* rc   = p->rchild;
	p->rchild  = rc->lchild;
	rc->lchild = p;
	p          = rc;
}

void rrotate(node*& p)
{
	node* lc   = p->lchild;
	p->lchild  = lc->rchild;
	lc->rchild = p;
	p          = lc;
}

void leftbalance(node*& t)
{
	node* lc = t->lchild;
	switch(lc->bf)
	{
		case 1: t->bf     = lc->bf = 0; rrotate(t); break;
		case -1: node* rd = lc->rchild;
		switch(rd->bf)
		{
			case 1: t->bf  = -1; lc->bf = 0;
			case 0: t->bf  = lc->bf = 0;
			case -1: t->bf = 0; lc->bf = 1;
		}
		rd->bf = 0;
		lrotate(t->lchild);
		rrotate(t);
	}
}

void rightbalance(node*& t)
{
	node* rc = t->rchild;
	switch(rc->bf)
	{
		case -1: t->bf   = rc->bf = 0; lrotate(t); break;
		case 1: node* ld = rc->lchild;
		switch(ld->bf)
		{
			case 1: t->bf  = 0; rc->bf = -1;
			case 0: t->bf  = rc->bf = 0;
			case -1: t->bf = 1; rc->bf = 0;
			ld->bf = 0;
			rrotate(t->rchild);
			lrotate(t);
		}
	}
}

int insert(node*& t, int e, bool& taller)
{
	if(!t)
	{
		t         = new node;
		t->data   = e;
		t->lchild = t->rchild = NULL;
		t->bf     = 0;
		taller    = true;
	}
	else
	{
		if(e == t->data) { taller = false; return 0; }
		if(e < t->data)
		{
			if(!insert(t->lchild, e, taller)) return 0;
			if(taller)
				switch(t->bf)
				{
					case 1: leftbalance(t); taller = false; break;
					case 0: t->bf  = 1; taller = true; break;
					case -1: t->bf = 0; taller = false; break;
				}
		}
		else
		{
			if(!insert(t->rchild, e, taller)) return 0;
			if(taller)
				switch(t->bf)
				{
					case 1: t->bf = 0; taller = false; break;
					case 0: t->bf = -1; taller = true; break;
					case -1: rightbalance(t); taller = false; break;
				}
		}
	}
	return 1;
}

void Bbtree::Insert(int e)
{
	bool taller = false;
	insert(root, e, taller);
}

void inordertraverse(node* t)
{
	if(t)
	{
		inordertraverse(t->lchild);
		cout << t->data << '\t';
		inordertraverse(t->rchild);
	}
}

void Bbtree::Inordertraverse()
{
	inordertraverse(root);
}

Bbtree::Bbtree(): root(NULL)
{
	ifstream input("E:\\重要文档\\programs\\data structure\\9 查找\\balanced binary tree.txt");
	assert(input);

	int e, cnt;
	input >> cnt;
	for(int i = 0; i < cnt; ++i)
	{
		input >> e;
		cout << e << '\t';
		Insert(e);
	}

	input.close();
}

void destruct(node*& t)
{
	if(t)
	{
		destruct(t->lchild);
		destruct(t->rchild);
		if(!t->lchild && !t->rchild) delete t;
	}
}

Bbtree::~Bbtree()
{
	destruct(root);
}

int main()
{
	Bbtree tree;
	tree.Inordertraverse();
	return 0;
}