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

typedef enum {RED, BLACK} COLOR;

typedef struct node
{
	int key;
	struct node *parent, *left, *right;
	COLOR color;
}node, *rbtree;

rbtree newnode(int x)
{
	rbtree p = new node;
	p->key = x;
	p->parent = p->left = p->right = NULL;
	p->color = RED;
	return p;
}

void Lrotate(rbtree root, rbtree nil, rbtree x)
{
	rbtree y = x->right;
	x->right = y->left;
	if(y->left != nil) y->left->parent = x;
	y->parent = x->parent;
	if(x->parent == nil) nil = y;
	else if(x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void Rrotate(rbtree root, rbtree nil, rbtree y)
{
	rbtree x = y->left;
	y->left = x->right;
	if(x->right != nil) x->right->parent = y;
	x->parent = y->parent;
	if(y->parent == nil) nil = x;
	else if(y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	x->right = y;
	y->parent = x;
}

void insert_fixup(rbtree root, rbtree nil, rbtree z)
{
	while(z->parent->color == RED)
	{
		if(z->parent == z->parent->parent->left)
		{
			rbtree y = z->parent->parent->right;
			if(y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z->parent->parent = z;
			}
			else
			{
				if(z == z->parent->right)
				{
					z = z->parent;
					Lrotate(root, nil, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				Rrotate(root, nil, z->parent->parent);
			}
		}
		else
		{
			rbtree y = z->parent->parent->left;
			if(y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z->parent->parent = z;
			}
			else
			{
				if(z == z->parent->left)
				{
					z = z->parent;
					Lrotate(root, nil, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				Rrotate(root, nil, z->parent->parent);
			}
		}
	}
}

class RBtree
{
public:
	RBtree();
	~RBtree() {}
	void insert(rbtree z);
private:
	rbtree root;
	rbtree nil;
};

void RBtree::insert(rbtree z)
{
	rbtree y = nil, x = root;
	while(x != nil)
	{
		y = x;
		x = (z->key < x->key)? x->left: x->right;
	}
	z->parent = y;
	if(y == nil) root = z;
	else if(z->key < y->key) y->left = z;
	else y->right = z;
	z->left = nil;
	z->right = nil;
	z->color = RED;
	insert_fixup(root, nil, z);
}

RBtree::RBtree(): root(NULL)
{
	nil = new node;
	nil->color = BLACK;

	ifstream input("E:\\重要文档\\programs\\data structure\\课设\\red-black tree.txt");
	int k;
	input >> k;
	root = newnode(k);
	while(input >> k)
	{
		rbtree p = newnode(k);
		insert(p);
	}
	input.close();
}

int main()
{
	RBtree tree;
	return 0;
}