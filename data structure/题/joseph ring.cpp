#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

typedef struct node
{
	int num;
	int code;
	struct node* next;
}node;

class JosephRing
{
public:
	JosephRing()
	{
		ifstream input("E:\\重要文档\\programs\\data structure\\题\\JosephRing.txt");
		if(!input)
		{
			cerr << "错误：文件打开失败！" << endl;
			exit(0);
		}

		input >> m >> n;

		node* p;
		for(int i = 0; i < n; ++i)
		{
			node* np = new node;
			np->num = i + 1;
			input >> np->code;
			np->next = NULL;
			if(!i) head = p = np;
			else
			{
				p->next = np;
				p = p->next;
			}
		}
		p->next = head;
		input.close();
	}

	~JosephRing()
	{
		if(n == 1) delete head;
		else
		{
			node* p = head;
			for(int i = 0; i < n; ++i)
				if(i != n - 1)
				{
					node* temp = p;
					p = p->next;
					delete temp;
				}
				else
				{
					delete p;
					break;
				}
		}
	}

	friend ostream& operator <<(ostream& output, const JosephRing& a)
	{
		node* p = a.head;
		for(int i = 0; i < a.n; ++i)
		{
			output << p->code << "\t";
			p = p->next;
		}
		return output;
	}

	void print_sequence()
	{
		node* p = head;
		for(; p->next != p; )
		{
			for(int i = 0; i < m - 2; ++i)
				p = p->next;
			cout << p->next->num << "\t";
			m = p->next->code;
			node* temp = p->next;
			p->next = p->next->next;
			p = p->next;
			delete temp;
			--n;
		}
		cout << p->num << "\t";
		delete p;
		--n;
		head = NULL;
		cout << endl;
	}

private:
	int m, n;
	node* head;
};

int main()
{
	JosephRing a;

	cout << a << endl;
	a.print_sequence();

	return 0;
}