//2-2
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef struct x
{
	int N;
	int n;
}X;

int main()
{
	int multiplicity, plural;

	ifstream ifile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-2\\input.txt");
	if(!ifile)
	{
		cout << "文件打开失败！" << endl;
	}
	else
	{
		int n, i, j, k, cnt, flag, value, pos;
		ifile >> n;
		cout << n << endl;
		vector<double> v(n);
		vector<X> _v(n);
		ifile >> v[0];
		cout << v[0] << " ";
		plural = _v[0].N = v[0];
		multiplicity = _v[0].n = 1;
		for(i = 1, cnt = 1; i < n; ++i)
		{
			ifile >> v[i];
			cout << v[i] << " ";
			for(j = 0, flag = 1; j < i; ++j)
			{
				if(v[i] == v[j])
				{
					flag = 0;
					value = v[j];
					break;
				}
			}
			if(flag)
			{
				_v[cnt].N = v[i];
				_v[cnt].n = 1;
				++cnt;
			}
			else
			{
				for(k = 0; k <= cnt; ++k)
				{
					if(_v[k].N == value)
					{
						pos = k;
						break;
					}
				}
				++_v[pos].n;
			}
		}
		for(i = 0; i < n; ++i)
		{
			if(_v[i].n > multiplicity)
			{
				multiplicity = _v[i].n;
				plural = _v[i].N;
			}
		}
		cout << endl << plural << endl << multiplicity << endl;

		ofstream ofile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\2-2\\output.txt");
		if(!ofile)
		{
			cout << "文件打开失败！" << endl;
		}
		else
		{
			ofile << plural << endl << multiplicity << endl;
			ofile.close();
		}
		ifile.close();
	}

	return 0;
}
