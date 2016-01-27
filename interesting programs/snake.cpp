#include <iostream>
#include <fstream>
#include <conio.h>
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

const int WIDTH  = 40;
const int LENGTH = 20;

vector<pair<int, int> > snake;
pair<int, int> food;
bool over          = false;
bool foodEaten     = false;
int shiftDirection = -1;
int direction;
/*
 * 0: up
 * 1: down
 * 2: left
 * 3: right
 */

inline bool gotoxy(int x, int y)
{
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD({x, y}));
}

inline void drawDot(int x, int y)
{
	gotoxy(x, y);
	cout << "*";
}

void drawClosure()
{
	for(int i = 0; i < 20; ++i)
		cout <<"* ";
	cout << endl;
	for(int i = 0; i < LENGTH - 2; ++i)
	{
		cout << "* ";
		for(int i = 0; i < 20 - 2; ++i)
			cout << "  ";
		cout << "* " << endl;
	}
	for(int i = 0; i < 20; ++i)
		cout << "* ";
}

bool okFood(int x, int y)
{
	for(int i = 0; i < snake.size(); ++i)
		if(snake[i].first == x && snake[i].second == y)
			return false;
	return true;
}

void generateFood()
{
	srand(unsigned(time(0)));
	food.first  = (rand() % 18 + 1) * 2;
	food.second = rand() % 18 + 1;
	while(!okFood(food.first, food.second))
	{
		food.first  = (rand() % 18 + 1) * 2;
		food.second = rand() % 18 + 1;
	}
	drawDot(food.first, food.second);
}

void init()
{
	drawClosure();

	srand(unsigned(time(0)));
	int x = (rand() % 18 + 1) * 2;
	int y = rand() % 18 + 1;
	snake.push_back(pair<int, int>(x, y));
	drawDot(x, y);

	generateFood();
	direction = rand() % 4;
}

int hitWallOrEatFoodOrEatBody()
/*
 * 0: will hit wall
 * 1: will eat food
 * 2: will eat body
 * 3: nothing will happen
 */
{
	int _x = snake[0].first;
	int _y = snake[0].second;
	switch(direction)
	{
		case 0: _y -= 1; break;
		case 1: _y += 1; break;
		case 2: _x -= 2; break;
		case 3: _x += 2; break;
	}
	if(_x == 0 || _x == WIDTH - 2 || _y == 0 || _y == LENGTH - 1)
		return 0;
	if(_x == food.first && _y == food.second)
		return 1;
	bool flag = false;
	for(int i = 0; i < snake.size(); ++i)
		if(snake[i].first == _x && snake[i].second == _y)
		{
			flag = true;
			break;
		}
	if(flag)
		return 2;

	return 3;
}

void move()
{
	if(!(shiftDirection == -1 
		|| (shiftDirection == 0 && direction == 1 || shiftDirection == 1 && direction == 0 
			|| shiftDirection == 2 && direction == 3 || shiftDirection == 3 && direction == 2)))
	{
		direction      = shiftDirection;
		shiftDirection = -1;
	}

	if(hitWallOrEatFoodOrEatBody() == 0 || hitWallOrEatFoodOrEatBody() == 2)
	{
		over = true;
		return;
	}
	if(hitWallOrEatFoodOrEatBody() == 1)
	{
		snake.insert(snake.begin(), pair<int, int>(food.first, food.second));
		foodEaten = true;
		return;
	}

	pair<int, int> tail = snake[snake.size() - 1];
	for(int i = snake.size() - 1; i >= 1; --i)
		snake[i] = snake[i - 1];

	gotoxy(tail.first, tail.second);
	cout << " ";
	switch(direction)
	{
		case 0: snake[0].second -= 1; break;
		case 1: snake[0].second += 1; break;
		case 2: snake[0].first  -= 2; break;
		case 3: snake[0].first  += 2; break;
	}
	drawDot(snake[0].first, snake[0].second);
}

void keyPressEvent()
{
	if(GetAsyncKeyState(VK_UP) < 0)
	{
		shiftDirection = 0;
		return;
	}
	if(GetAsyncKeyState(VK_DOWN) < 0)
	{
		shiftDirection = 1;
		return;
	}
	if(GetAsyncKeyState(VK_LEFT) < 0)
	{
		shiftDirection = 2;
		return;
	}
	if(GetAsyncKeyState(VK_RIGHT) < 0)
	{
		shiftDirection = 3;
		return;
	}
	shiftDirection = -1;
}

void play()
{
	while(!over)
	{
		keyPressEvent();
		move();
		if(foodEaten)
		{
			generateFood();
			foodEaten = false;
		}
		Sleep(100);
	}
}

int main()
{
	init();
	play();
	return 0;
}