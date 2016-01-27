#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void display(const vector<int>& v)
{
	for(auto& p: v) cout << p << " ";
	cout << endl;
}

int arrangement(const vector<int>& v)
{
	vector<int> _v(v);
	sort(_v.begin(),_v.end());
	int i = 0;
	do
	{
	   display(_v);
	   ++i;
	}while(next_permutation(_v.begin(), _v.end()));
	return i;
}

int combination(int m, const vector<int>& v)
{
	int n = v.size();
	vector<int> f;
	f.insert(f.end(), m, 1);
	f.insert(f.end(), n - m, 0);
	vector<int> _v;
	int cnt = 0;
	do
	{
		for(int i = 0;i != f.size();++i)
		{
			if(f[i])
			{
				_v.push_back(v[i]);
			}
		}
		display(_v);
		++cnt;
		_v.clear();
	}while(prev_permutation(f.begin(), f.end()));

	return cnt;
}

int main()
{
	vector<int> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v.push_back(9);
	v.push_back(0);
	cout << "arrangement:" << endl;
	cout << arrangement(v) << endl;
	cout << "combination:" << endl;
	cout << combination(v.size(), v) << endl;
	return 0;
}
