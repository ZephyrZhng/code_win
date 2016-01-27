#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <windows.h>

using namespace std;

const int LIMIT = 2048;

vector<vector<int> > v(4);

void display()
{
	for(int i = 0; i < v.size(); ++i)
	{
		for(int j = 0; j < v[i].size(); ++j)
			cout << v[i][j] << "\t";
		cout << endl;
	}
}

void randTile()
{
	srand(unsigned(time(0)));
	int x = rand() % 4;
	int y = rand() % 4;
	while(v[x][y])
	{
		x = rand() % 4;
		y = rand() % 4;
	}
	int val = (rand() % 2 + 1) * 2;
	v[x][y] = val;
}

void init()
{
	for(int i = 0; i < v.size(); ++i)
		for(int j = 0; j < 4; ++j)
			v[i].push_back(0);

	randTile();
	randTile();
}

int findMax()
{
	int m = 0;
	for(int i = 0; i < v.size(); ++i)
		for(int j = 0; j < v[i].size(); ++j)
			if(v[i][j] > m)
				m = v[i][j];
	return m;
}

void tighten(vector<int>& myVector)
{
	vector<int> _myVector(myVector.size(), 0);
	int  i = 0; 
	int _i = 0;
	for(; i < myVector.size(); ++i)
		if(myVector[i])
			_myVector[_i++] = myVector[i];
	copy(_myVector.begin(), _myVector.end(), myVector.begin());
}

void merge(vector<int>& myVector)
{
	for(int i = 0; i < myVector.size() - 1; )
	{
		if(myVector[i + 1] == myVector[i])
		{
			myVector[i]     *= 2;
			myVector[i + 1]  = 0;
			i               += 2;
		}
		else ++i;
	}
}

void moveUp()
{
	for(int j = 0; j < 4; ++j)
	{
		vector<int> myVector;
		for(int i = 0; i < 4; ++i)
			myVector.push_back(v[i][j]);

		tighten(myVector);
		merge  (myVector);
		tighten(myVector);

		for(int i = 0; i < 4; ++i)
			v[i][j] = myVector[i];
	}
}

void moveDown()
{
	for(int j = 0; j < 4; ++j)
	{
		vector<int> myVector;
		for(int i = 3; i >= 0; --i)
			myVector.push_back(v[i][j]);

		tighten(myVector);
		merge  (myVector);
		tighten(myVector);

		for(int i = 3; i >= 0; --i)
			v[i][j] = myVector[3 - i];
	}
}

void moveLeft()
{
	for(int i = 0; i < 4; ++i)
	{
		tighten(v[i]);
		merge  (v[i]);
		tighten(v[i]);
	}
}

void moveRight()
{
	for(int i = 0; i < 4; ++i)
	{
		reverse(v[i].begin(), v[i].end());
		tighten(v[i]);
		merge  (v[i]);
		tighten(v[i]);
		reverse(v[i].begin(), v[i].end());
	}
}

void play()
{
	while(findMax() < LIMIT)
	{
		bool isFull = true;
		for(int i = 0; i < v.size(); ++i)
			for(int j = 0; j < v[i].size(); ++j)
				if(!v[i][j])
				{
					isFull = false;
					break;
				}
		if(isFull)
		{
			cout << "you lose" << endl;
			return;
		}

		char action;
		cin >> action;
		switch(action)
		{
			case 'w': moveUp();		break;
			case 's': moveDown();	break;
			case 'a': moveLeft();	break;
			case 'd': moveRight();	break;
		}
		randTile();
		system("cls");
		display();
	}
	cout << "you win" << endl;
}

int main()
{
	init();
	display();
	play();
	return 0;
}
