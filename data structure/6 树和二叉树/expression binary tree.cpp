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
	int ltag, rtag;//0->child/1->thread
}node;

int T[7][7] = {
	{1,	1,	-1,	-1,	-1,	1,	1},
	{1,	1,	-1,	-1,	-1,	1,	1},
	{1,	1,	1,	1,	-1,	1,	1},
	{1,	1,	1,	1,	-1,	1,	1},
	{-1,-1,	-1,	-1,	-1,	0,	-2},
	{1,	1,	1,	1,	-2,	1,	1},
	{-1,-1,	-1,	-1,	-1,	-2,	0}
};

int coordinate(char theta)
{
	switch(theta)
	{
		case '+': return 0;
		case '-': return 1;
		case '*': return 2;
		case '/': return 3;
		case '(': return 4;
		case ')': return 5;
		case '#': return 6;
	}
}

inline int precede(char theta1, char theta2)
{
	return T[coordinate(theta1)][coordinate(theta2)];
}

void CrtNode(node*& t, char ch, stack<node*>& pt)
{
	t         = new node;
	t->data   = ch;
	t->lchild = NULL;
	t->rchild = NULL;
	pt.push(t);
}

void CrtSubtree(node*& t, char ch, stack<node*>& pt)
{
	t         = new node;
	t->data   = ch;

	t->rchild = pt.top();
	pt.pop();

	t->lchild = pt.top();
	pt.pop();

	pt.push(t);
}

void pre(node* t)
{
	if(t)
	{
		cout << t->data;
		pre(t->lchild);
		pre(t->rchild);
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

void post(node* t)
{
	if(t)
	{
		post(t->lchild);
		post(t->rchild);
		cout << t->data;
	}
}

void cnt_leaf(node* t, int& cnt)
{
	if(t)
	{
		if(!(t->lchild) && !(t->rchild)) ++cnt;
		cnt_leaf(t->lchild, cnt);
		cnt_leaf(t->rchild, cnt);
	}
}

int cal_depth(node* t)
{
	if(!t) return 0;
	else
		return max(cal_depth(t->lchild), cal_depth(t->rchild)) + 1;
}

void delete_node(node*& t)
{
	if(t)
	{
		if(!t->ltag) delete_node(t->lchild);
		if(!t->rtag) delete_node(t->rchild);
		if(t->ltag && t->rtag) delete t;
	}
}

node* create_node(char i, node* lp, node* rp)
{
	node* p   = new node;
	p->data   = i;
	p->lchild = lp;
	p->rchild = rp;
	return p;
}

node* copy_tree(node* t)
{
	if(!t) return NULL;
	node *lp, *rp, *p;
	if(t->lchild)
		lp = copy_tree(t->lchild);
	else lp = NULL;
	if(t->rchild)
		rp = copy_tree(t->rchild);
	else rp = NULL;
	p = create_node(t->data, lp, rp);
	return p;
}

int cnt_x_node(node* t, char x, int& cnt)
{
	if(t)
	{
		if(t->data == x) ++cnt;
		cnt_x_node(t->lchild, x, cnt);
		cnt_x_node(t->rchild, x, cnt);
	}
}

void delete_leaf(node*& t)
{
	if(t)
	{
		if(!(t->lchild->lchild) && !(t->lchild->rchild))
		{
			node *lp  = t->lchild;
			t->lchild = NULL;
			delete lp;
		}
		if(!(t->rchild->lchild) && !(t->rchild->rchild))
		{
			node *rp  = t->rchild;
			t->rchild = NULL;
			delete rp;
		}
		delete_leaf(t->lchild);
		delete_leaf(t->rchild);
	}
}

void swaplr(node*& t)
{
	if(t)
	{
		swap(t->lchild, t->rchild);
		swaplr(t->lchild);
		swaplr(t->rchild);
	}
}

void find(node* t, char x, node*& p)
{
	if(t)
	{
		if(t->data == x)
		{
			p = t;
			return;
		}
		find(t->lchild, x, p);
		find(t->rchild, x, p);
	}
}

bool is_descendant(node* t, node* p)
{
	if(t)
	{
		if(t == p || is_descendant(t->lchild, p) || is_descendant(t->rchild, p)) return true;
		else return false;
	}
}

bool belong_to_different_subtree(node* t, node* p, node* q)
{
	if(t)
	{
		bool taglp, tagrp, taglq, tagrq;
		if(t->lchild)
		{
			taglp = is_descendant(t->lchild, p);
			taglq = is_descendant(t->lchild, q);
		}
		if(t->rchild)
		{
			tagrp = is_descendant(t->rchild, p);
			tagrq = is_descendant(t->rchild, q);
		}
		if((taglp && tagrq) || (tagrp && taglq)) return true;
		else return false;
	}
}

void least_common_ancestor(node* t, node* p, node* q, node*& ptr)
{
	if(t)
	{
		if(belong_to_different_subtree(t, p, q))
		{
			ptr = t;
			return;
		}
		else
		{
			node* pnext;
			if(is_descendant(t->lchild, p) && is_descendant(t->lchild, q)) pnext = t->lchild;
			if(is_descendant(t->rchild, p) && is_descendant(t->rchild, q)) pnext = t->rchild;
			least_common_ancestor(pnext, p, q, ptr);
		}
	}
}

class bt
{
public:
	bt();//zyh
	bt(const bt& _t): t(copy_tree(_t.t)){}//zyh
	~bt(){delete thr; delete_node(t);}//zyh
	void PreorderTraverse(){pre(t);}//czx
	void InorderTraverse(){in(t);}//czx
	void PostorderTraverse(){post(t);}//czx
	void PreorderTraverse_NonRecursive();//zyh
	void InorderTraverse_NonRecursive();//zyh
	void PostorderTraverse_NonRecursive();//zyh
	void LevelTraverse();//zyh
	int CountLeaf(){return leaf;}//lbp
	int GetDepth(){return depth;}//lbp
	int CntXNode(char x){int cnt(0); cnt_x_node(t, x, cnt); return cnt;}//lbp
	void DeleteLeaf(){delete_leaf(t);}//lbp
	void SwapLR(){swaplr(t);}//lbp
	char LeastCommonAncestor(char p, char q);//mpc
	bool Complete();//czx
	void InorderThreading();//mpc
	void InorderTraverse_Thr();//mpc
private:
	node* t;
	int leaf;
	int depth;
	node* thr;
};

bt::bt(): leaf(0)
{
	ifstream input("E:\\重要文档\\programs\\data structure\\6 树和二叉树\\expression binary tree.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}
	string exp;
	input >> exp;
	cout << exp << endl;
	input.close();

	stack<char> s;
	s.push('#');
	stack<node*> pt;
	int i(0);
	char ch(exp[i]);

	while(!(s.top() == '#' && ch == '#'))
	{
		if(isalpha(ch))
			CrtNode(t, ch, pt);
		else
		{
			switch(ch)
			{
				case '(': {s.push(ch); break;}
				case ')':
				{
					char c = s.top();
					s.pop();
					while(c != '(')
					{
						CrtSubtree(t, c, pt);
						c = s.top();
						s.pop();
					}
					break;
				}
				default:
				{
					char c = s.top();
					while(!s.empty() && precede(c, ch) == 1)
					{
						CrtSubtree(t, c, pt);
						s.pop();
						c = s.top();
					}
					if(ch != '#')
						s.push(ch);
					break;
				}
			}
		}

		if(ch != '#')
			ch = exp[++i];
	}

	t = pt.top();
	pt.pop();

	cnt_leaf(t, leaf);
	depth = cal_depth(t);
}

void bt::PreorderTraverse_NonRecursive()
{
	stack<node*> s;
	node* p = t;
	while(p || !s.empty())
		if(p)
		{
			s.push(p);
			cout << p->data;
			p = p->lchild;
		}
		else
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
}

void bt::InorderTraverse_NonRecursive()
{
	stack<node*> s;
	node* p = t;
	while(p || !s.empty())
		if(p)
		{
			s.push(p);
			p = p->lchild;
		}
		else
		{
			p = s.top();
			s.pop();
			cout << p->data;
			p = p->rchild;
		}
}

typedef struct se
{
	node* p;
	int i;
}se;

void bt::PostorderTraverse_NonRecursive()
{
	stack<se> s;
	node* p = t;
	int tag = 0;
	while(p || !s.empty())
		if(p)
			switch(tag)
			{
				case 0: {se temp = {p, ++tag}; s.push(temp); tag = 0; p = p->lchild; break;}
				case 1: {se temp = {p, ++tag}; s.push(temp); tag = 0; p = p->rchild; break;}
				case 2: {
					cout << p->data;
					if(!s.empty())
					{
						p   = s.top().p;
						tag = s.top().i;
						s.pop();
						break;
					}
					else p = NULL;
				}
			}
		else
		{
			p   = s.top().p;
			tag = s.top().i;
			s.pop();
		}
}

void bt::LevelTraverse()
{
	if(t)
	{
		queue<node*> q;
		q.push(t);
		while(!q.empty())
		{
			node* p = q.front();
			q.pop();
			cout << p->data;
			if(p->lchild) q.push(p->lchild);
			if(p->rchild) q.push(p->rchild);
		}
	}
}

char bt::LeastCommonAncestor(char p, char q)
{
	node *pp(NULL), *pq(NULL);
	find(t, p, pp);
	find(t, q, pq);
	node* pa(NULL);
	least_common_ancestor(t, pp, pq, pa);
	return pa->data;
}

bool bt::Complete()
{
	if(t)
	{
		bool tag(true);
		queue<node*> q;
		q.push(t);
		while(!q.empty())
		{
			node* p = q.front();
			q.pop();
			if(p->lchild)
			{
				if(tag) q.push(p->lchild);
				else return false;
			}
			else tag = false;
			if(p->rchild)
			{
				if(tag) q.push(p->rchild);
				else return false;
			}
		}
	}
	return true;
}

void in_thr(node*& t, node*& pre)
{
	if(t->lchild)
	{
		t->ltag = 0;
		in_thr(t->lchild, pre);
	}
	else
	{
		t->ltag   = 1;
		t->lchild = pre;
	}
	if(pre && pre->rtag) pre->rchild = t;
	pre = t;
	if(t->rchild)
	{
		t->rtag = 0;
		in_thr(t->rchild, pre);
	}
	else t->rtag = 1;
}

void bt::InorderThreading()
{
	thr         = new node;
	thr->ltag   = 0;
	thr->rtag   = 1;
	thr->rchild = thr;
	thr->lchild = t;

	node* pre   = thr;
	in_thr(t, pre);

	pre->rchild = thr;
	pre->rtag   = 1;
	thr->rchild = pre;
}

void bt::InorderTraverse_Thr()
{
	node* p = t;
	while(p != thr)
	{
		while(!p->ltag) p = p->lchild;
		cout << p->data;
		while(p->rtag && p->rchild != thr)
		{
			p = p->rchild;
			cout << p->data;
		}
		p = p->rchild;
	}
}

int main()
{
	bt t;
	//bt _t(t);

	//_t.PreorderTraverse(); cout << endl;

	t.PreorderTraverse(); cout << endl;
	t.InorderTraverse(); cout << endl;
	t.PostorderTraverse(); cout << endl;
	t.LevelTraverse(); cout << endl;
	cout << t.CountLeaf() << endl;
	cout << t.GetDepth() << endl;
	cout << t.CntXNode('-') << endl;
	//t.DeleteLeaf(); t.LevelTraverse(); cout << endl;
	//t.SwapLR(); t.LevelTraverse(); cout << endl;
	//cout << t.LeastCommonAncestor('a', 'c') << endl;

	/*
	node *px, *py;
	find(t.t, 'c', px); //cout << px->data << endl;
	find(t.t, 'a', py); //cout << py->data << endl;
	//cout << is_descendant(t.t, px) << endl;
	//cout << belong_to_different_subtree(t.t, px, py) << endl;
	node* ptr;
	least_common_ancestor(t.t, px, py, ptr);
	cout << ptr->data << endl;
	*/
	cout << t.LeastCommonAncestor('a', 'c') << endl;
	cout << t.Complete() << endl;
	t.PreorderTraverse_NonRecursive(); cout << endl;
	t.InorderTraverse_NonRecursive(); cout << endl;
	t.PostorderTraverse_NonRecursive(); cout << endl;
	t.InorderThreading(); t.InorderTraverse_Thr(); cout << endl;

	return 0;
}