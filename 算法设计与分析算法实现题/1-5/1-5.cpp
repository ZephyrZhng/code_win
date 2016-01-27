//1-5
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void ShellSort(vector<double> &v, int n)
{
	int gap, i, j;
	double temp;

	for(gap = n / 2; gap > 0; gap /= 2)
	{
		for(i = gap; i < n; ++i)
		{
			for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
			{
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
			}
		}
	}
}

int main()
{
	ifstream ifile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\1-5\\input.txt");
	if(!ifile)
	{
		cout << "文件打开失败！" << endl;
	}
	else
	{
		int n;
		ifile >> n;
		cout << n << endl;
		vector<double> v(n);
		for(int i = 0; i < n; ++i)
		{
			ifile >> v[i];
			cout << v[i] << " ";
		}
		cout << endl;
		ShellSort(v, n);

		int i;
		double difference, _difference;
		for(i = 0, difference = 0; i < n - 1; ++i)
		{
			_difference = v[i + 1] - v[i];
			if(_difference > difference)
			{
				difference = _difference;
			}
		}
		cout << difference << endl;

		ofstream ofile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\1-5\\output.txt");
		if(!ofile)
		{
			cout << "文件打开失败！" << endl;
		}
		else
		{
			ofile << difference;
			ofile.close();
		}
		ifile.close();
	}

	return 0;
}