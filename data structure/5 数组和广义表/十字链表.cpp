#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

typedef struct OLNode
{
	int i, j;
	int e;
	struct OLNode *right, *down;
}OLNode, *OLink;

template<class T>
void ShellSort (vector<T>& v)
{
	for(int gap = v.size() / 2; gap > 0; gap /= 2)
		for(int i = gap; i < v.size(); ++i)
			for(int j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
				swap(v[j], v[j + gap]);
}

void display(const vector<OLNode>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i].i << "\t" << v[i].j << "\t" << v[i].e << endl;
	cout << endl;
}

void display(const vector< vector<OLNode> >& v)
{
	for(int i = 0; i < v.size(); ++i)
		display(v[i]);
	cout << endl;
}

void link(OLink& rp0, OLink& dp0, OLink np)
{
	if(!rp0) rp0 = np;
	else
	{
		OLink rp = rp0;
		for(; rp->right; rp = rp->right);
		rp->right = np;
	}
	if(!dp0) dp0 = np;
	else
	{
		OLink dp = dp0;
		for(; dp->down; dp = dp->down);
		dp->down = np;
	}
}

OLink new_node(int i, int j, int e)
{
	OLink np = new OLNode;
	np->i = i;
	np->j = j;
	np->e = e;
	np->right = np->down = NULL;
	return np;
}

class OrthogonalList
{
public:
	OrthogonalList(){}

	OrthogonalList(int _x, int _y): x(_x), y(_y)
	{
		rhead.resize(x);
		chead.resize(y);
		for(int i = 0; i < x; ++i)
			rhead[i] = NULL;
		for(int i = 0; i < y; ++i)
			chead[i] = NULL;
	}

	OrthogonalList(const OrthogonalList& a): x(a.x), y(a.y)
	{
		//深复制
		rhead.resize(x);
		chead.resize(y);
		for(int i = 0; i < x; ++i)
			rhead[i] = NULL;
		for(int i = 0; i < y; ++i)
			chead[i] = NULL;
		for(int i = 0; i < x; ++i)
			for(OLink pj = a.rhead[i]; pj; pj = pj->right)
			{
				OLink np = new_node(pj->i, pj->j, pj->e);
				link(rhead[i], chead[pj->j], np);
			}
	}

	~OrthogonalList()
	{
		for(int i = 0; i < x; ++i)
			for(OLink p = rhead[i]; p; )
			{
				OLink temp = p;
				p = p->right;
				delete temp;
			}
	}

	void create()
	{
		ifstream input("E:\\重要文档\\programs\\data structure\\5 数组和广义表\\data.txt");
		if(!input)
		{
			cerr << "错误：文件打开失败！" << endl;
			exit(0);
		}
		input >> x >> y >> n;
		//cout << x << "\t" << y << "\t" << n << endl;
		vector<OLNode> v;
		for(int i = 0; i < n; ++i)
		{
			OLNode temp;
			input >> temp.i >> temp.j >> temp.e;
			//cout << temp.i << "\t" << temp.j << "\t" << temp.e << endl;
			v.push_back(temp);
		}
		input.close();

		for(int gap = v.size() / 2; gap > 0; gap /= 2)
			for(int i = gap; i < v.size(); ++i)
				for(int j = i - gap; j >= 0 && v[j].i > v[j + gap].i; j -= gap)
					swap(v[j], v[j + gap]);
		//cout << endl; display(v); cout << endl;

		vector< vector<OLNode> > m;
		for(; v.size(); )
		{
			int j;
			for(j = 1; j < v.size() && v[j].i == v[j - 1].i; ++j);
			vector<OLNode> mi(j);
			copy(v.begin(), v.begin() + j, mi.begin());
			v.erase(v.begin(), v.begin() + j);
			m.push_back(mi);
		}
		for(int k = 0; k < m.size(); ++k)
			for(int gap = m[k].size() / 2; gap > 0; gap /= 2)
				for(int i = gap; i < m[k].size(); ++i)
					for(int j = i - gap; j >= 0 && m[k][j].j > m[k][j + gap].j; j -= gap)
						swap(m[k][j], m[k][j + gap]);
		//display(m);

		rhead.resize(x);
		chead.resize(y);
		for(int i = 0; i < x; ++i)
			rhead[i] = NULL;
		for(int i = 0; i < y; ++i)
			chead[i] = NULL;
		for(int i = 0; i < m.size(); ++i)
			for(int j = 0; j < m[i].size(); ++j)
			{
				OLink np = new_node(m[i][j].i, m[i][j].j, m[i][j].e);
				link(rhead[m[i][j].i], chead[m[i][j].j], np);
			}

	}

	friend ostream& operator <<(ostream& output, const OrthogonalList& m)
	{
		for(int i = 0; i < m.x; ++i)
		{
			if(!m.rhead[i]) continue;
			for(OLink p = m.rhead[i]; p; p = p->right)
				output << p->i << "\t" << p->j << "\t" << p->e << endl;
			output << endl;
		}
		return output;
	}

	void print_by_colum()
	{
		for(int j = 0; j < y; ++j)
		{
			if(!chead[j]) continue;
			for(OLink p = chead[j]; p; p = p->down)
				cout << p->i << "\t" << p->j << "\t" << p->e << endl;
			cout << endl;
		}
	}

	friend OrthogonalList operator +(const OrthogonalList& a, const OrthogonalList& b)
	{
		if(a.x != b.x || a.y != b.y)
		{
			cerr << "错误：无法相加！" << endl;
			exit(0);
		}
		int x(a.x), y(a.y);
		OrthogonalList ans(x, y);
		for(int i = 0; i < x; ++i)
		{
			OLink pa(a.rhead[i]), pb(b.rhead[i]);
			for(; pa && pb; )
			{
				if(pa->j == pb->j && pa->e + pb->e)
				{
					OLink np = new_node(pa->i, pa->j, pa->e + pb->e);
					link(ans.rhead[i], ans.chead[pa->j], np);
					pa = pa->right;
					pb = pb->right;
					continue;
				}
				if(pa->j > pb->j)
				{
					OLink np = new_node(pb->i, pb->j, pb->e);
					link(ans.rhead[i], ans.chead[pb->j], np);
					pb = pb->right;
					continue;
				}
				if(pb->j > pa->j)
				{
					OLink np = new_node(pa->i, pa->j, pa->e);
					link(ans.rhead[i], ans.chead[pa->j], np);
					pa = pa->right;
					continue;
				}
			}
			if(pa || pb)
				for(OLink tail = (!pa)? pb: pa; tail; tail = tail->right)
				{
					OLink np = new_node(tail->i, tail->j, tail->e);
					link(ans.rhead[tail->i], ans.chead[tail->j], np);
				}
		}

		return ans;
	}

	friend OrthogonalList operator *(const OrthogonalList& a, const OrthogonalList& b)
	{
		if(a.y != b.x)
		{
			cerr << "错误：无法相乘！" << endl;
			exit(0);
		}
		int x(a.x), y(b.y);
		OrthogonalList ans(x, y);
		for(int i = 0; i < x; ++i)
			for(int j = 0; j < y; ++j)
			{
				OLink pa(a.rhead[i]), pb(b.chead[j]);
				int temp(0);
				for(; pa && pb; )
					if(pa->i == pb->j)
						temp += pa->e * pb->e;
				if(temp)
				{
					OLink np = new_node(i, j, temp);
					link(ans.rhead[i], ans.chead[j], np);
				}
			}
	}

	friend OrthogonalList operator *(const OrthogonalList& a, int b)
	{
		OrthogonalList ans(a);
		for(int i = 0; i < ans.x; ++i)
			for(OLink p = ans.rhead[i]; p; p = p->right)
				p->e *= b;
		return ans;
	}

	friend OrthogonalList operator *(int b, const OrthogonalList& a)
	{
		return a * b;
	}

	OrthogonalList& operator =(const OrthogonalList& a)
	{
		if(this->x != a.x || this->y != a.y)
		{
			cerr << "错误：无法赋值！" << endl;
			exit(0);
		}
		for(int i = 0; i < x; ++i)
			for(OLink p = rhead[i]; p; )
			{
				OLink temp = p;
				p = p->right;
				delete temp;
			}
		for(int i = 0; i < x; ++i)
			rhead[i] = NULL;
		for(int i = 0; i < y; ++i)
			chead[i] = NULL;
		for(int i = 0; i < x; ++i)
			for(OLink pj = a.rhead[i]; pj; pj = pj->right)
			{
				OLink np = new_node(pj->i, pj->j, pj->e);
				link(rhead[i], chead[pj->j], np);
			}
		return *this;
	}

	friend OrthogonalList operator -(const OrthogonalList& a, const OrthogonalList& b)
	{
		if(a.y != b.x)
		{
			cerr << "错误：无法相乘！" << endl;
			exit(0);
		}
		OrthogonalList ans(a.x, b.y);
		ans = a + b * -1;
		return ans;
	}

private:
	int x;//矩阵的行数
	int y;//矩阵的列数
	int n;//非零元素的个数
	vector<OLink> rhead;//row head
	vector<OLink> chead;//colum head
};

int main()
{
	OrthogonalList l;
	l.create();
	OrthogonalList r(l);

	OrthogonalList ans(l);
	ans = 2 * l + r;
	cout << ans << endl;

	return 0;
}