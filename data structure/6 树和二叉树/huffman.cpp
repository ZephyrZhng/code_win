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
	double weight;
	int parent, lchild, rchild;
}node;

template<class t>
void display(const vector<t>& v)
{
	for(int i = 0; i < v.size(); ++i) cout << v[i] << "\t";
	cout << endl;
}

template<class t>
void display(const vector< vector<t> >& v)
{
	for(int i = 0; i < v.size(); ++i) display(v[i]);
}

void FindMax(vector<node>& ht, double& max, int& pos)
{
	for(int i = 0; i < ht.size(); ++i)
		if(ht[i].parent == -1 && ht[i].weight > max)
		{
			max = ht[i].weight;
			pos = i;
		}
	ht[pos].parent = ht.size();
}

void CreateHuffmanTree(const vector<double>& w, vector<node>& ht)
{
	for(int i = 0; i < w.size(); ++i)
	{
		node n = {w[i], -1, -1, -1};
		ht.push_back(n);
	}
	for(int i = 0; i < w.size() - 1; ++i)
	{
		double max1(0), max2(0);
		int pos1(-1), pos2(-1);
		FindMax(ht, max1, pos1);
		FindMax(ht, max2, pos2);
		node n = {max1 + max2, -1, pos2, pos1};
		ht.push_back(n);
	}
}

void GenerateHuffmanCode(const vector<node>& ht, vector< vector<int> >& hc)
{
	for(int i = 0; i < (ht.size() + 1) / 2; ++i)
	{
		vector<int> hci;
		hc.push_back(hci);
		int j(ht[i].parent), k(i);
		for(; j != -1; k = j, j = ht[j].parent)
		{
			if(k == ht[j].lchild) hc[i].insert(hc[i].begin(), 0);
			if(k == ht[j].rchild) hc[i].insert(hc[i].begin(), 1);
		}
	}
}

void WriteHuffmanTree(const vector<node>& ht)
{
	ofstream output("E:\\重要文档\\programs\\data structure\\6 树和二叉树\\huffman tree.txt");
	if(!output)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	for(int i = 0; i < ht.size(); ++i)
		output << i << "\t" << ht[i].parent << "\t" << ht[i].lchild << "\t" << ht[i].rchild << endl;

	output.close();
}

void ReadHuffmanTree(vector<node>& ht)
{
	ifstream input("E:\\重要文档\\programs\\data structure\\6 树和二叉树\\huffman tree.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	int i;
	while(input >> i)
	{
		node n;
		input >> n.parent >> n.lchild >> n.rchild;
		ht.push_back(n);
	}

	input.close();
}

void decode(const vector<node>& ht)
{
	ifstream input("E:\\重要文档\\programs\\data structure\\6 树和二叉树\\huffman code.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	char c;
	while(input >> c)
	{
		int code  = c - '0';
		int i = code? ht[ht.size() - 1].rchild: ht[ht.size() - 1].lchild;
		while(ht[i].lchild != -1)
		{
			input >> c;
			code = c - '0';
			i    = code? ht[i].rchild: ht[i].lchild;
		}
		char txt = 'A' + i;
		cout << txt;
	}
	cout << endl;

	input.close();
}

int main()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\6 树和二叉树\\huffman.txt");
	if(!input)
	{
		cerr << "错误：文件打开失败！" << endl;
		exit(0);
	}

	double weight;
	vector<double> w;
	while(input >> weight) w.push_back(weight);
	display(w);

	input.close();

	vector<node> ht;
	vector< vector<int> > hc;
	CreateHuffmanTree(w, ht);
	GenerateHuffmanCode(ht, hc);
	display(hc);

	vector<node> testtree;
	ReadHuffmanTree(testtree);
	decode(testtree);

	return 0;
}