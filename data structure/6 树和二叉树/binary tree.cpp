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

typedef struct node
{
	char data;
	node *lchild, *rchild;
}node;

void delete_node(node*& t)
{
	if(t)
	{
		delete_node(t->lchild);
		delete_node(t->rchild);
		if(!t->lchild && !t->rchild) delete t;
	}
}

void in(node* t)
{
	if(t)
	{
		in(t->lchild);
		cout << t->data;
		in(t->rchild);
	}
}

class bt
{
public:
	bt();
	~bt(){delete_node(t);}
	void InorderTraverse(){in(t);}
private:
	node* t;
};

bt::bt()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\6 树和二叉树\\binary tree.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	char parent, child, tag;
	queue<node*> q;
	input >> parent >> child >> tag;
	cout << parent << child << tag << endl;
	node* p   = new node;
	p->data   = child;
	p->lchild = p->rchild = NULL;
	q.push(p);
	t = p;
	input >> parent >> child >> tag;
	cout << parent << child << tag << endl;

	while(parent != '#')
	{
		node* p = new node;
		p->data = child;
		p->lchild = p->rchild = NULL;
		while(q.front()->data != parent) q.pop();
		if(tag == 'L') q.front()->lchild = p;
		if(tag == 'R') q.front()->rchild = p;
		q.push(p);
		input >> parent >> child >> tag;
		cout << parent << child << tag << endl;
	}

	input.close();
}

int main()
{
	bt t;

	t.InorderTraverse(); cout << endl;

	return 0;
}