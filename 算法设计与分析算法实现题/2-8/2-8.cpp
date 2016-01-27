//2-8
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

template<class Type>
inline void Swap (Type& a, Type& b)
{
	Type temp = a; a = b; b = temp;
}

void Perm (string s, int k, int m, vector<string>& v)
{
	if(k == m)
	{
		cout << s << endl;
		v.push_back (s);
	}
	else
		for(int i = k; i <= m; ++i)
		{
			Swap (s[k], s[i]);
			Perm (s, k + 1, m, v);
			Swap (s[k], s[i]);
		}
}

int main ()
{
	ifstream ifile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-8\\input.txt");
	if(!ifile) cout << "文件打开失败！" << endl;
	else
	{
		int n, cnt;
		string s;
		vector<string> v;

		ifile >> n;
		cout << n << endl;
		ifile >> s;
		cout << s << endl;
		Perm (s, 0, n - 1, v);
		sort (v.begin(), v.end());
		v.erase (unique (v.begin(), v.end()), v.end());
		cnt = v.size();
		ofstream ofile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-8\\output.txt");
		if(!ofile) cout << "文件打开失败！" << endl;
		else
		{
			for(int i = 0; i < cnt; ++i)
			{
				ofile << v[i] << endl;
				cout << v[i] << " ";
			}
			ofile << cnt << endl;
			cout << endl << cnt << endl;
			ofile.close();
		}
		ifile.close();
	}

	return 0;
}