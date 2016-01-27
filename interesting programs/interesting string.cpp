/*
输入一个仅含abc的字符串，将其中所有连续的两个不同的字母换成另外一个，
如：出现ab则换成c，求最终得到的最短的字符串。
*/
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

bool check(const string& s)
{
	if(s.size() == 1)
	{
		return true;
	}
	for(int i = 1; i < s.size(); ++i)
	{
		if(s[i] != s[0])
		{
			return false;
		}
	}
	return true;
}

char replace(const char& ch1, const char& ch2)
{
	if((ch1 == 'a' && ch2 == 'b') || (ch2 == 'a' && ch1 == 'b')) return 'c';
	if((ch1 == 'a' && ch2 == 'c') || (ch2 == 'a' && ch1 == 'c')) return 'b';
	if((ch1 == 'c' && ch2 == 'b') || (ch2 == 'c' && ch1 == 'b')) return 'a';
}

void DELETE(string& s)
{
	if(check(s))
	{
		cout << s << endl;
	}
	else
	{
		for(int i = 1; i < s.size(); ++i)
		{
			if(s[i] != s[0])
			{
				string::iterator it = s.begin();
				s[i - 1] = replace(s[i], s[0]);
				s.erase(it + i);
				break;
			}
		}
		DELETE(s);
	}
}

int main()
{
	string s;

	cin >> s;
	DELETE(s);

	return 0;
}