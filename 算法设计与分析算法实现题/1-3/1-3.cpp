//1-3
#include <iostream>
#include <fstream>
using namespace std;

int div(int n)
{
	int i, cnt;

	for(i = 1, cnt = 0; i <= n; ++i)
	{
		if(!(n % i))
		{
			++cnt;
		}
	}

	return cnt;
}

int main()
{
	ifstream ifile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\1-3\\input.txt");

	if(!ifile)
	{
		cout << "文件打开失败！" << endl;
	}
	else
	{
		int begin, end, max, result;

		ifile >> begin >> end;
		cout << begin << " " << end << endl;

		int i, divisor;
		for(max = result = 2, i = begin; i <= end; ++i)
		{
			divisor = div(i);
			if(divisor > max)
			{
				result = divisor;
			}
		}
		cout << result << endl;

		ofstream ofile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\1-3\\output.txt");
		if(!ofile)
		{
			cout << "文件打开失败！" << endl;
		}
		else
		{
			ofile << result << endl;
			ofile.close();
		}

		ifile.close();
	}

	return 0;
}