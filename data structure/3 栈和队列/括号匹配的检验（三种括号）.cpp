#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

#define left true
#define right false

bool  direction(char c)
{
	if(c == '(' || c == '[' || c == '{') return left;
	if(c == ')' || c == ']' || c == '}') return right;
}

char matchchar(char c)
{
	switch(c)
	{
		case ')': return '(';
		case ']': return '[';
		case '}': return '{';
	}
}

bool match()
{
	stack<char> s;
	char c;
	bool ans(true);
	for(; cin >> c; )
	{
		if(direction(c) == right)
			if(s.empty() || s.top() != matchchar(c))
				ans = false;
			else s.pop();
		else s.push(c);
	}
	return ans;
}

int main()
{
	cout << match() << endl;

	return 0;
}