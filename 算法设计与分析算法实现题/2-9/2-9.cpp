//2-9
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
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
	ifstream ifile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-9\\input.txt");
	if(!ifile) cout << "文件打开失败！" << endl;
	else
	{
		int n, cnt, value;
		string sss;
		vector<string> v;
		vector<string>::iterator it;

		ifile >> n;
		cout << n << endl;
		string s (n, '0'), ss (n, '0');
		for(int i = 0; i < n; ++i)
		{
			s[i] += i + 1;
			ifile >> ss[i];
		}
		Perm (s, 0, n - 1, v); cout << endl;
		sort (v.begin(), v.end());
		for(int i = 0; i < v.size(); ++i) cout << v[i] << endl;
		it = find (v.begin(), v.end(), ss);
		value = it - v.begin();
		sss = *(it + 1);
		cout << value << endl << sss << endl;
		ofstream ofile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-9\\output.txt");
		if(!ofile) cout << "文件打开失败！" << endl;
		else
		{
			ofile << value << endl;
			for(int i = 0; i < n; ++i) ofile << sss[i] << " "; ofile << endl;
			ofile.close();
		}
		ifile.close();
	}

	return 0;
}