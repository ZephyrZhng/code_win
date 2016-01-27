#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;

typedef struct pos
{
	int x;
	int y;
}pos;

bool legal(const vector<pos>& chess)
{
	set<int> x, y;
	for(int i = 0; i < chess.size(); ++i)
	{
		x.insert(chess[i].x);
		y.insert(chess[i].y);
	}
	return (x.size() == chess.size() && y.size() == chess.size());
}

void trial(int i, int n, vector<pos>& chess, long long& cnt)
{
	if(i > n) //输出棋盘当前布局
	{
		++cnt;
		cout << cnt << "\t";
		for(int i = 0; i < chess.size(); ++i)
			cout << "(" << chess[i].x << "," << chess[i].y << ")\t";
		cout << endl;
	}
	else
		for(int j = 1; j <= n; ++j)
		{
			//在第i行第j列放置一个棋子；
			pos p = {i, j};
			chess.push_back(p);
			if(legal(chess)/*当前布局合法*/) trial(i + 1, n, chess, cnt);
			//移走第i行第j列的棋子；
			chess.erase(chess.end() - 1);
		}
}

int main()
{
	vector<pos> chess;
	long long n, cnt(0);
	cin >> n;
	trial(1, n, chess, cnt);
	cout << cnt << endl;
	return 0;
}