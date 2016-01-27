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
	struct node *lchild, *rchild;
	int data;
}node, *bstree;

class Bstree
{
public:
	Bstree();
	~Bstree();
	node* search(int key);
	void insert(int x);
	void deletebst(int x);
	void InOrderTraverse();
private:
	bstree root;
};

Bstree::Bstree(): root(NULL)
{
	ifstream input("E:\\重要文档\\programs\\data structure\\9 查找\\binary search tree.txt");
	assert(input);

	int key;
	while(input >> key)
	{
		if(!root)
		{
			node *p   = new node;
			p->data   = key;
			p->lchild = p->rchild = NULL;
			root      = p;
			continue;
		}

		node *p = root, *f = NULL;
		while(p)
		{
			if(p->data == key) break;
			else if(key > p->data) {f = p; p = p->rchild;}
			else {f = p; p = p->lchild;}
		}
		if(!p)
		{
			node* n   = new node;
			n->data   = key;
			n->lchild = n->rchild = NULL;
			if(key > f->data) f->rchild = n;
			else f->lchild = n;
		}
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

Bstree::~Bstree()
{
	destruct(root);
}

void inordertraverse(node* t)
{
	if(t)
	{
		inordertraverse(t->lchild);
		cout << t->data << "\t";
		inordertraverse(t->rchild);
	}
}

void Bstree::InOrderTraverse()
{
	inordertraverse(root);
}

node* searchbst(node* t, int key)
{
	if(!t || key == t->data) return t;
	else if(key < t->data) return searchbst(t->lchild, key);
	else return searchbst(t->rchild, key);
}

bool searchbst(node* t, int key, node* f, node*& p)
{
	if(!t) { p = f; return false; }
	else if(key == t->data) { p = t; return true; }
	else if(key < t->data) return searchbst(t->lchild, key, t, p);
	else return searchbst(t->rchild, key, t, p);
}

node* Bstree::search(int key)
{
	return searchbst(root, key);
}

void Bstree::insert(int x)
{
	node* p = NULL;
	if(!searchbst(root, x, NULL, p))
	{
		node* s   = new node;
		s->data   = x;
		s->lchild = s->rchild = NULL;
		if(!p) root = s;
		else if(x < p->data) p->lchild = s;
		else p->rchild = s;
	}
}

void Delete(node*& p)
{
	if(!p->rchild)
	{
		node* q = p;
		p       = p->lchild;
		delete q;
	}
	else if(!p->lchild)
	{
		node* q = p;
		p       = p->rchild;
		delete q;
	}
	else
	{
		node *q = p, *s = p->lchild;
		while(s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		p->data = s->data;
		if(q != p) q->rchild = s->lchild;
		else q->lchild = s->lchild;
		delete s;
	}
}

void Deletebst(node*& t, int key)
{
	assert(t);
	if(key == t->data) Delete(t);
	else if(key < t->data) Deletebst(t->lchild, key);
	else Deletebst(t->rchild, key);
}

void Bstree::deletebst(int x)
{
	Deletebst(root, x);
}

int main()
{
	Bstree tree;
	tree.InOrderTraverse();
	cout << tree.search(4)->data << endl;
	tree.deletebst(4);
	tree.InOrderTraverse(); cout << endl;
	tree.insert(11);
	tree.InOrderTraverse();
	return 0;
}