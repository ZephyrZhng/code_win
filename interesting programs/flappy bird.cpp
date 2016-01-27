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

const int WIDTH           = 80;
const int HEIGHT          = 20;
const int SLIT_HEIGHT     = 5;
const int PILLAR_WIDTH    = 3;
const int PILLAR_INTERVAL = 5;

typedef struct
{
	int x;
	int y;
}position;
position birdPosition = position({WIDTH / 2, HEIGHT / 2});

typedef struct
{
	int position;
	int height;
}pillarState;

vector<pillarState> pillar;
bool over = false;

inline bool gotoxy(int x, int y)
{
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD({x, y}));
}

inline void drawBird(int x, int y)
{
	gotoxy(x, y);
	cout << "*";
}

inline void drawPillar(int x, int y)
{
	gotoxy(x, y);
	cout << "口";
}

void init()
{
	gotoxy(0, 0);
	for(int i = 0; i < WIDTH; ++i)
		cout << "-";
	gotoxy(0, 21);
	for(int i = 0; i < WIDTH; ++i)
		cout << "-";
	drawBird(WIDTH / 2, HEIGHT / 2);
}

void generatePillar()
{
	srand(unsigned(time(0)));
	int pos = (rand() % 5) + 6;
	for(int i = 1; i <= pos; ++i)
		drawPillar(WIDTH - 2, i);
	gotoxy(WIDTH - 2, pos + SLIT_HEIGHT + 1);
	for(int i = pos + SLIT_HEIGHT + 1; i <= HEIGHT; ++i)
		drawPillar(WIDTH - 2, i);
	pillar.push_back(pillarState({78, pos}));
}

void movePillar(int i)
{
	for(int j = 1; j <= pillar[i].height; ++j)
	{
		if(pillar[i].position >= 2)
			drawPillar(pillar[i].position - 2, j);
		if(pillar[i].position <= 74)
		{
			gotoxy(pillar[i].position + 4, j);
			cout << " ";
		}
	}
	for(int j = pillar[i].height + SLIT_HEIGHT + 1; j <= 20; ++j)
	{
		if(pillar[i].position >= 2)
			drawPillar(pillar[i].position - 2, j);
		if(pillar[i].position <= 74)
		{
			gotoxy(pillar[i].position + 4, j);
			cout << " ";
		}
	}
	pillar[i].position -= 2;
}

void movePicture()
{
	for(int i = 0; i < pillar.size(); ++i)
	{
		movePillar(i);
	}
	if(pillar[0].position == -6)
		pillar.erase(pillar.begin());
	if(pillar[pillar.size() - 1].position == 62)
		generatePillar();
}

void fall()
{
	gotoxy(birdPosition.x, birdPosition.y);
	cout << " ";
	birdPosition.y += 1;
	drawBird(birdPosition.x, birdPosition.y);
}

void fly()
{
	gotoxy(birdPosition.x, birdPosition.y);
	cout << " ";
	birdPosition.y -= 2;
	drawBird(birdPosition.x, birdPosition.y);
}

bool hitGround()
{
	return birdPosition.y == 20;
}

bool hitFloor()
{
	return birdPosition.y == 1;
}

bool hitPillar()
{
	for(int i = 0; i < pillar.size(); ++i)
	{
		if ((birdPosition.x >= pillar[i].position - 1 && birdPosition.x <= pillar[i].position + 6) &&
			(birdPosition.y <= pillar[i].height + 1   || birdPosition.y >= pillar[i].height   + SLIT_HEIGHT))
			return true;
	}
	return false;
}

void keyPressEvent()
{
	if(GetAsyncKeyState(VK_SPACE) < 0)
		fly();
}

void clearScreen()
{
	for(int i = 1; i <= 20; ++i)
	{
		gotoxy(0, i);
		for(int i = 0; i < WIDTH; ++i)
			cout << " ";
	}
}

void addTime(char startTime[10], char endTime[10], int timeInterval)
{
	strcpy(endTime, startTime);
	int hour   = (startTime[0] - '0') * 10 + (startTime[1] - '0');
	int minute = (startTime[3] - '0') * 10 + (startTime[4] - '0');
	int second = (startTime[6] - '0') * 10 + (startTime[7] - '0');

	second += timeInterval;
	if(second >= 60)
	{
		minute += second / 60;
		second %= 60;
		if(minute >= 60)
		{
			hour += minute / 60;
			minute %= 60;
		}
	}
	endTime[0] = '0' + hour   / 10;
	endTime[1] = '0' + hour   % 10;
	endTime[3] = '0' + minute / 10;
	endTime[4] = '0' + minute % 10;
	endTime[6] = '0' + second / 10;
	endTime[7] = '0' + second % 10;
}

void play()
{
	init();

	time_t t = time(0);
	char startTime[10];
	strftime(startTime, sizeof(startTime), "%X", localtime(&t));

	char endTime[10];
	addTime(startTime, endTime, 3);

	char currentTime[10];
	strcpy(currentTime, startTime);

	while(strcmp(currentTime, endTime))
	{
		time_t _t = time(0);
		strftime(currentTime, sizeof(currentTime), "%X", localtime(&_t));

		keyPressEvent();
		fall();
		if(hitGround() || hitFloor())
			over = true;
		Sleep(100);
	}

	generatePillar();

	while(!over)
	{
		movePicture();
		keyPressEvent();
		fall();
		if(hitGround() || hitFloor() || hitPillar())
			over = true;
		Sleep(100);
	}
	clearScreen();
	gotoxy(WIDTH / 2, HEIGHT / 2);
	cout << "you lose" << endl;
	system("pause");
}

int main()
{
	play();

	return 0;
}
