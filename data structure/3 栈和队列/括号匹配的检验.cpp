#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;

bool match()
{
	char c;
	stack<char> s;
	cin >> c;
	if(c == ']' || c == ')')
		return false;
	s.push(c);
	for(; cin >> c; )
	{
		if(c == '[' || c == '(')
		{
			s.push(c);
			continue;
		}
		if(c == ')' && s.top() == '(')
		{
			s.pop();
			continue;
		}
		if(c == ']' && s.top() == '[')
		{
			s.pop();
			continue;
		}
	}
	if(s.empty()) return true;
	else return false;
}

int main()
{
	cout << match() << endl;

	return 0;
}