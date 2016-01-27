/*
project euler problem 19
You are given the following information, but you may prefer to do some research for yourself.
1 Jan 1900 was a Monday. 
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine. 
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400. 
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/
#include <iostream>
using namespace std;

const int begin_year = 1901;
const int end_year = 2000;

//蔡勒公式：w = (y + int(y / 4) + int(c / 4) - 2 * c + int(26 * (m + 1) / 10) + d - 1) % 7;
/*
w:星期
c:世纪数减1(年份前两位数)
y:年（两位数）
m:月（m大于等于3，小于等于14，即1、2月看作上一年的13、14月）
d:日
*/
int cal_day(int d, int m, int y, int c)
{
	int w;

	c = y / 100;
	if(m == 1)
	{
		m = 13;
		--y;
	}
	if(m == 2)
	{
		m = 14;
		--y;
	}
	y %= 100;
	w = (y + int(y / 4) + int(c / 4) - 2 * c + int(26 * (m + 1) / 10) + d - 1) % 7;

	return w;
}

int main()
{
	int month, year, century, cnt;

	for(year = begin_year, cnt = 0; year <= end_year; ++year)
	{
		for(month = 1; month <= 12; ++month)
		{
			century = year / 100;
			if(!cal_day(1, month, year, century))
			{
				cout << year << " " << month << " " << 1 << endl;
				++cnt;
			}
		}
	}
	cout << cnt << endl;

	return 0;
}
