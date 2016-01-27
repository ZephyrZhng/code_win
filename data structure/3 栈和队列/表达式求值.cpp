#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
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

int T[7][7] = {
	1,	1,	-1,	-1,	-1,	1,	1,
	1,	1,	-1,	-1,	-1,	1,	1,
	1,	1,	1,	1,	-1,	1,	1,
	1,	1,	1,	1,	-1,	1,	1,
	-1,	-1,	-1,	-1,	-1,	0,	-2,
	1,	1,	1,	1,	-2,	1,	1,
	-1,	-1,	-1,	-1,	-1,	-2,	0
};

int coordinate(char theta)
{
	switch(theta)
	{
		case '+': return 0;
		case '-': return 1;
		case '*': return 2;
		case '/': return 3;
		case '(': return 4;
		case ')': return 5;
		case '#': return 6;
	}
}

inline int precede(char theta1, char theta2)
{
	return T[coordinate(theta1)][coordinate(theta2)];
}

inline int toNum(char c)
{
	return c - '0';
}

long double operate(long double a, char theta, long double b)
{
	switch(theta)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
}

long double EvaluateExpression()
{
	stack<long double>	OPND;
	stack<char>			OPTR;
	stack<char>			track;
	OPTR.push('#');
	char c;
	cin >> c;
	for(; c != '#' || OPTR.top() != '#'; )
	{
		if(isdigit(c))
		{
			if(!track.empty() && isdigit(track.top()))
			{
				OPND.top() = OPND.top() * 10 + toNum(c);
				track.push(c);
				cin >> c;
				continue;
			}
			else
			{
				OPND.push(toNum(c));
				track.push(c);
				cin >> c;
				continue;
			}
		}
		switch(precede(OPTR.top(), c))
		{
			case -1: OPTR.push(c); track.push(c); cin >> c; break;
			case 0: OPTR.pop(); track.push(c); cin >> c; break;
			case 1:
			long double b = OPND.top();
			OPND.pop();
			long double a = OPND.top();
			OPND.pop();
			char theta = OPTR.top();
			OPTR.pop();
			OPND.push(operate(a, theta, b));
			break;
		}
	}

	return OPND.top();
}

int main()
{
	cout << EvaluateExpression() << endl;

	return 0;
}