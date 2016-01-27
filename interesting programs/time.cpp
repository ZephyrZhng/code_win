#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
#include <windows.h>
using namespace std;

/*BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
得到高精度计时器的值(如果存在这样的计时器)。
BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
返回硬件支持的高精度计数器的频率（次每秒），返回0表示失败。
LARGE_INTEGER
它是一个联合体，可以得到__int64 QuadPart;也可以分别得到低32位DWORD LowPart和高32位的值LONG HighPart。
在使用时，先使用QueryPerformanceFrequency()得到计数器的频率，
再计算二次调用QueryPerformanceCounter()所得的计时器值之差，用差去除以频率就得到精确的计时了。
头文件：windows.h*/

int main()
{
	LARGE_INTEGER  u;
	double f;
	__int64  val1, val2;

	QueryPerformanceFrequency(&u);
	f = u.QuadPart;
	QueryPerformanceCounter(&u);
	val1 = u.QuadPart;
	for(int i = 0; i < 1e8; ++i);
	QueryPerformanceCounter(&u);
	val2 = u.QuadPart;

	cout << "本机高精度计时器频率" << f << endl;
	cout << "第一次计时器值" << val1 << endl;
	cout << "第二次计时器值" << val2 << endl;
	cout << "计时器值之差" << val2 - val1 << endl;
	cout << "计时" << (val2 - val1) * 1000 / f << "ms" << endl;

	return 0;
}