//2-6
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

string num2str(int i)
{
	stringstream s;

	s << i;

	return s.str();
}

void GenerateSet (string s, int x, vector<string>& v)
{
	if(!x)
	{
		s.erase (s.end() - 1, s.end());
		reverse (s.begin(), s.end());
		v.push_back (s);
		cout << s << endl;
	}
	else
		for(int i = int(x / 2); i >= 0; --i)
		{
			string temp = num2str (i);
			reverse (temp.begin(), temp.end());
			GenerateSet (s + temp, i, v);
		}
}

int main ()
{
	ifstream ifile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-6\\input.txt");
	if(!ifile) cout << "文件打开失败！" << endl;
	else
	{
		int n, cnt;
		vector<string> v;

		ifile >> n;
		cout << n << endl;
		string N = num2str(n);
		reverse (N.begin(), N.end());
		GenerateSet (N, n, v);
		sort (v.begin(), v.end());
		v.erase (unique (v.begin(), v.end()), v.end());
		cnt = v.size();
		for(int i = 0; i < cnt; ++i) cout << v[i] << " "; cout << endl;
		cout << cnt;
		ofstream ofile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-6\\output.txt");
		if(!ofile) cout << "文件打开失败！" << endl;
		else
		{
			ofile << cnt << endl;
			ofile.close();
		}
		ifile.close();
	}

	return 0;
}