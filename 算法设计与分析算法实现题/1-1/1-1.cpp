//1-1
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
	int n;
	int num[10];

	memset(num, 0, sizeof(num));

	ifstream ifile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\1-1\\input.txt");
	if(!ifile)
	{
		cout << "文件打开失败！" << endl;
	}
	else
	{
		ifile >> n;
		cout << n << endl << endl;

		for(int i  = 1; i <= n; ++i)
		{
			for(int j = i; j > 0; j /= 10)
			{
				switch(j % 10)
				{
					case 0: ++num[0]; break;
					case 1: ++num[1]; break;
					case 2: ++num[2]; break;
					case 3: ++num[3]; break;
					case 4: ++num[4]; break;
					case 5: ++num[5]; break;
					case 6: ++num[6]; break;
					case 7: ++num[7]; break;
					case 8: ++num[8]; break;
					case 9: ++num[9]; break;
				}
			}
		}
		for(int i = 0; i < 10; ++i)
		{
			cout << num[i] << endl;
		}

		ofstream ofile("E:\\重要文档\\programs\\算法设计与分析算法实现题\\1-1\\output.txt");
		if(!ofile)
		{
			cout << "文件打开失败！" << endl;
		}
		else
		{
			for(int i = 0; i < 10; ++i)
			{
				ofile << num[i] << endl;
			}
			ofile.close();
		}

	ifile.close();
	}

	return 0;
}