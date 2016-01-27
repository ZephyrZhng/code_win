/*
In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:

High Card:			Highest value card.
One Pair:			Two cards of the same value.
Two Pairs:			Two different pairs.
Three of a Kind:	Three cards of the same value.
Straight: 			All cards are consecutive values.
Flush: 				All cards of the same suit.
Full House: 		Three of a kind and a pair.
Four of a Kind: 	Four cards of the same value.
Straight Flush: 	All cards are consecutive values of same suit.
Royal Flush: 		Ten, Jack, Queen, King, Ace, in same suit.

The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

1.If two players have the same ranked hands then the rank made up of the highest value wins;
for example, a pair of eights beats a pair of fives (see example 1 below).

2.But if two ranks tie, for example, both players have a pair of queens,
then highest cards in each hand are compared (see example 4 below);

3.if the highest cards tie then the next highest cards are compared, and so on.
Consider the following five hands dealt to two players:

Hand		Player 1			Player 2		Winner

1		5H 5C 6S 7S KD		2C 3S 8S 8D TD		Player 2
		Pair of Fives		Pair of Eights

2		5D 8C 9S JS AC 		2C 5C 7D 8S QH
		Highest card Ace  	Highest card Queen  Player 1

3   	2D 9C AS AH AC 		3D 6D 7D TD QD		Player 2
		Three Aces   		Flush with Diamonds

4   	4D 6S 9H QH QC 		3D 6D 7H QD QS 		Player 1
		Pair of Queens 		Pair of Queens
		Highest card Nine 	Highest card Seven

5   	2H 2D 4C 4D 4S 		3C 3D 3S 9S 9D 		Player 1
		Full House   		Full House
		With Three Fours  	with Three Threes

The file, poker.txt, contains one-thousand random hands dealt to two players.
Each line of the file contains ten cards (separated by a single space):
the first five are Player 1's cards and the last five are Player 2's cards.
You can assume that all hands are valid (no invalid characters or repeated cards),
each player's hand is in no specific order, and in each hand there is a clear winner.

How many hands does Player 1 win?
*/
// supposed to output 376 while output 377
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
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
#include <windows.h>

using namespace std;

class HAND
{
public:
								HAND() {}
	void						read(ifstream& f);
	void						display();
	int							rank();
	void						sort();

	vector< pair<int, char> >	hand;

	int							onePair_Value;

	int							twoPairs_Value1;
	int							twoPairs_Value2;

	int							threeOfAKind_Value;

	int							straight_LowestValue;

	char						flush_Suit;

	int							fullHouse_ThreeOfAKind_Value;
	int							fullHouse_Pair_Value;

	int							fourOfAKind_Value;

	int							straightFlush_LowestValue;
	char 						straightFlush_Suit;

	char 						royalFlush_Suit;

	int							highCard();
	bool						onePair();
	bool						twoPairs();
	bool						threeOfAKind();
	bool						straight();
	bool						flush();
	bool						fullHouse();
	bool						fourOfAKind();
	bool						straightFlush();
	bool						royalFlush();
};

void HAND::read(ifstream& f)
{
	hand.resize(5);

	onePair_Value                = 0;
	
	twoPairs_Value1              = 0;
	twoPairs_Value2              = 0;
	
	threeOfAKind_Value           = '$';
	
	straight_LowestValue         = 0;
	
	flush_Suit                   = '$';
	
	fullHouse_ThreeOfAKind_Value = 0;
	fullHouse_Pair_Value         = 0;
	
	fourOfAKind_Value            = 0;
	
	straightFlush_LowestValue    = 0;
	straightFlush_Suit           = '$';
	
	royalFlush_Suit              = '$';

	for(int i = 0; i < 5; ++i)
	{
		char value;
		f >> value;
		if(isdigit(value))
		{
			hand[i].first = value - '0';
		}
		else
		{
			switch(value)
			{
				case 'T': hand[i].first = 10; break;
				case 'J': hand[i].first = 11; break;
				case 'Q': hand[i].first = 12; break;
				case 'K': hand[i].first = 13; break;
				case 'A': hand[i].first = 14; break;
			}
		}
		f >> hand[i].second;
	}
}

void HAND::display()
{
	for(int i = 0; i < hand.size(); ++i)
	{
		cout << hand[i].first << hand[i].second << " ";
	}
	cout << endl;
}

int HAND::highCard()
{
	int h = 0;
	for(int i = 0; i < hand.size(); ++i)
	{
		if(hand[i].first > h)
		{
			h = hand[i].first;
		}
	}
	return h;
}

bool HAND::onePair()
{
	for(int i = 0; i < hand.size(); ++i)
	{
		for(int j = i + 1; j < hand.size(); ++j)
		{
			if(hand[i].first == hand[j].first)
			{
				onePair_Value = hand[i].first;
				return true;
			}
		}
	}
	return false;
}

bool HAND::twoPairs()
{
	bool flag1 = false;
	bool flag2 = false;
	vector< pair<int, char> > _hand(hand);
	int i, j;
	for(i = 0; i < hand.size(); ++i)
	{
		for(j = i + 1; j < hand.size(); ++j)
		{
			if(hand[i].first == hand[j].first)
			{
				twoPairs_Value1 = hand[i].first;
				flag1           = true;
				break;
			}
		}
	}
	if(!flag1)
	{
		return flag1;
	}
	_hand.erase(_hand.begin() + i);
	_hand.erase(_hand.begin() + j);
	for(i = 0; i < _hand.size(); ++i)
	{
		for(j = i + 1; j < _hand.size(); ++j)
		{
			if(_hand[i].first == _hand[j].first && _hand[i].first != twoPairs_Value1)
			{
				twoPairs_Value2 = _hand[i].first;
				flag2           = true;
				break;
			}
		}
	}
	return flag2;
}

bool HAND::threeOfAKind()
{
	for(int i = 0; i < hand.size(); ++i)
	{
		for(int j = i + 1; j < hand.size(); ++j)
		{
			for(int k = j + 1; k < hand.size(); ++k)
			{
				if(hand[i].first == hand[j].first && hand[i].first == hand[k].first)
				{
					threeOfAKind_Value = hand[i].first;
					return true;
				}
			}
		}
	}
	return false;
}

bool HAND::straight()
{
	for(int i = 0; i < hand.size(); ++i)
	{
		for(int j = i + 1; j < hand.size(); ++j)
		{
			if(hand[j].first < hand[i].first)
			{
				swap(hand[j], hand[i]);
			}
		}
	}
	for(int i = 0; i < hand.size() - 1; ++i)
	{
		if(hand[i + 1].first != hand[i].first + 1)
		{
			return false;
		}
	}
	straight_LowestValue = hand[0].first;
	return true;
}

bool HAND::flush()
{
	for(int i = 0; i < hand.size() - 1; ++i)
	{
		if(hand[i].second != hand[i + 1].second)
		{
			return false;
		}
	}
	flush_Suit = hand[0].second;
	return true;
}

bool  HAND::fullHouse()
{
	for(int i = 0; i < hand.size(); ++i)
	{
		for(int j = i + 1; j < hand.size(); ++j)
		{
			if(hand[i].first == hand[j].first)
			{
				fullHouse_Pair_Value = hand[i].first;
				vector< pair<int, char> > _hand(hand);
				_hand.erase(_hand.begin() + i);
				_hand.erase(_hand.begin() + j);
				if(_hand[0].first == _hand[1].first && _hand[0].first == _hand[2].first)
				{
					fullHouse_ThreeOfAKind_Value = _hand[0].first;
					return true;
				}
			}
		}
	}
	return false;
}

bool HAND::fourOfAKind()
{
	for(int i = 0; i < hand.size(); ++i)
	{
		vector< pair<int, char> > _hand(hand);
		_hand.erase(_hand.begin() + i);
		bool flag = true;
		for(int i = 0; i < _hand.size() - 1; ++i)
		{
			if(_hand[i].first != _hand[i + 1].first)
			{
				flag = false;
			}
		}
		if(flag)
		{
			return true;
		}
	}
	return false;
}

bool HAND::straightFlush()
{
	if(straight() && flush())
	{
		straightFlush_LowestValue = straight_LowestValue;
		straightFlush_Suit        = flush_Suit;
		return true;
	}
	else
	{
		return false;
	}
}

bool HAND::royalFlush()
{
	return (straightFlush() && straightFlush_LowestValue == 10)? true: false;
}

void HAND::sort()
{
	for(int i = 0; i < hand.size(); ++i)
	{
		for(int j = i + 1; j < hand.size(); ++j)
		{
			if(hand[j].first < hand[i].first)
			{
				swap(hand[j], hand[i]);
			}
		}
	}
}

int HAND::rank()
{
	if(royalFlush())	{cout << "royal flush" << endl;		return 9;}
	if(straightFlush())	{cout << "straight flush" << endl;	return 8;}
	if(fourOfAKind())	{cout << "four of a kind" << endl;	return 7;}
	if(fullHouse())		{cout << "full house" << endl;		return 6;}
	if(flush())			{cout << "flush" << endl;			return 5;}
	if(straight())		{cout << "straight" << endl;		return 4;}
	if(threeOfAKind())	{cout << "three of a kind" << endl;	return 3;}
	if(twoPairs())		{cout << "two pairs" << endl;		return 2;}
	if(onePair())		{cout << "one pair" << endl;		return 1;}
						 cout << "high card" << endl;		return 0;
}

int main()
{
	ifstream f("E:\\document\\programs\\project_euler\\pe_54\\poker.txt");

	int winner1  = 0;

	for(int i = 0; i < 1000; ++i)
	{
		cout << i + 1 << endl;
		HAND player1, player2;
		player1.read(f);
		player2.read(f);

		player1.display();
		int rank1 = player1.rank();
		player2.display();
		int rank2 = player2.rank();
		cout << endl;

		if(rank1 > rank2)
		{
			++winner1;
		}
		else if(rank1 == rank2)
		{
			switch(rank1)
			{
				case 8: {
					if(player1.straightFlush_LowestValue > player2.straightFlush_LowestValue)
					{
						++winner1;
						continue;
					}
					else if(player1.straightFlush_LowestValue < player2.straightFlush_LowestValue)
					{
						continue;
					}
					break;
				}
				case 7: {
					if(player1.fourOfAKind_Value > player2.fourOfAKind_Value)
					{
						++winner1;
						continue;
					}
					else if(player1.fourOfAKind_Value < player2.fourOfAKind_Value)
					{
						continue;
					}
					break;
				}
				case 6: {
					if(player1.fullHouse_ThreeOfAKind_Value > player2.fullHouse_ThreeOfAKind_Value)
					{
						++winner1;
						continue;
					}
					else if(player1.fullHouse_ThreeOfAKind_Value < player2.fullHouse_ThreeOfAKind_Value)
					{
						continue;
					}
					else
					{
						if(player1.fullHouse_Pair_Value > player2.fullHouse_Pair_Value)
						{
							++winner1;
							continue;
						}
						else if(player1.fullHouse_Pair_Value < player2.fullHouse_Pair_Value)
						{
							continue;
						}
					}
					break;
				}
				case 4: {
					if(player1.straight_LowestValue > player2.straight_LowestValue)
					{
						++winner1;
						continue;
					}
					else if(player1.straight_LowestValue < player2.straight_LowestValue)
					{
						continue;
					}
					break;
				}
				case 3: {
					if(player1.threeOfAKind_Value > player2.threeOfAKind_Value)
					{
						++winner1;
						continue;
					}
					else if(player1.threeOfAKind_Value < player2.threeOfAKind_Value)
					{
						continue;
					}
					break;
				}
				case 2: {
					int twoPairs_MaxValue1 = (player1.twoPairs_Value1 > player1.twoPairs_Value2)? player1.twoPairs_Value1: player1.twoPairs_Value2;
					int twoPairs_MinValue1 = (player1.twoPairs_Value1 < player1.twoPairs_Value2)? player1.twoPairs_Value1: player1.twoPairs_Value2;
					int twoPairs_MaxValue2 = (player2.twoPairs_Value1 > player2.twoPairs_Value2)? player2.twoPairs_Value1: player2.twoPairs_Value2;
					int twoPairs_MinValue2 = (player2.twoPairs_Value1 < player2.twoPairs_Value2)? player2.twoPairs_Value1: player2.twoPairs_Value2;
					if(twoPairs_MaxValue1 > twoPairs_MaxValue2)
					{
						++winner1;
						continue;
					}
					else if(twoPairs_MaxValue1 < twoPairs_MaxValue2)
					{
						continue;
					}
					else
					{
						if(twoPairs_MinValue1 > twoPairs_MinValue2)
						{
							++winner1;
							continue;
						}
						else if(twoPairs_MinValue1 < twoPairs_MinValue2)
						{
							continue;
						}
					}
					break;
				}
				case 1: {
					if(player1.onePair_Value > player2.onePair_Value)
					{
						++winner1;
						continue;
					}
					else if(player1.onePair_Value < player2.onePair_Value)
					{
						continue;
					}
					break;
				}
				case 0: {
					if(player1.highCard() > player2.highCard())
					{
						++winner1;
						continue;
					}
					else if(player1.highCard() < player2.highCard())
					{
						continue;
					}
					break;
				}
			}

			switch(rank1)
			{
				case 7: {
					int _1, _2;
					for(int j = 0; j < player1.hand.size(); ++j)
					{
						if(player1.hand[j].first != player1.fourOfAKind_Value)
						{
							_1 = player1.hand[j].first;
							break;
						}
					}
					for(int j = 0; j < player2.hand.size(); ++j)
					{
						if(player2.hand[j].first != player2.fourOfAKind_Value)
						{
							_2 = player2.hand[j].first;
							break;
						}
					}
					if(_1 > _2)
					{
						++winner1;
					}
					break;
				}
				case 3: {
					vector< pair<int, char> > v1(player1.hand);
					vector< pair<int, char> > v2(player2.hand);
					for(int j = 0; j < 3; ++j)
					{
						for(int k = 0; k < v1.size(); ++k)
						{
							if(v1[k].first == player1.threeOfAKind_Value)
							{
								v1.erase(v1.begin() + k);
								break;
							}
						}
					}
					for(int j = 0; j < 3; ++j)
					{
						for(int k = 0; k < v2.size(); ++k)
						{
							if(v2[k].first == player2.threeOfAKind_Value)
							{
								v2.erase(v2.begin() + k);
								break;
							}
						}
					}
					int max1 = max(v1[0].first, v1[1].first);
					int min1 = min(v1[0].first, v1[1].first);
					int max2 = max(v2[0].first, v2[1].first);
					int min2 = min(v2[0].first, v2[1].first);
					if(max1 > max2)
					{
						++winner1;
					}
					else if(max1 == max2)
					{
						if(min1 > min2)
						{
							++winner1;
						}
					}
					break;
				}
				case 2: {
					vector< pair<int, char> > v1(player1.hand);
					vector< pair<int, char> > v2(player2.hand);
					for(int j = 0; j < 2; ++j)
					{
						for(int k = 0; k < v1.size(); ++k)
						{
							if(v1[k].first == player1.twoPairs_Value1);
							{
								v1.erase(v1.begin() + k);
								break;
							}
						}
					}
					for(int j = 0; j < 2; ++j)
					{
						for(int k = 0; k < v1.size(); ++k)
						{
							if(v1[k].first == player1.twoPairs_Value2);
							{
								v1.erase(v1.begin() + k);
								break;
							}
						}
					}
					for(int j = 0; j < 2; ++j)
					{
						for(int k = 0; k < v2.size(); ++k)
						{
							if(v2[k].first == player2.twoPairs_Value1);
							{
								v2.erase(v2.begin() + k);
								break;
							}
						}
					}
					for(int j = 0; j < 2; ++j)
					{
						for(int k = 0; k < v2.size(); ++k)
						{
							if(v2[k].first == player2.twoPairs_Value2);
							{
								v2.erase(v2.begin() + k);
								break;
							}
						}
					}
					if(v1[0].first > v2[0].first)
					{
						++winner1;
					}
					break;
				}
				case 1: {
					vector< pair<int, char> > v1(player1.hand);
					vector< pair<int, char> > v2(player2.hand);
					for(int j = 0; j < 2; ++j)
					{
						for(int k = 0; k < v1.size(); ++k)
						{
							if(v1[k].first == player1.onePair_Value)
							{
								v1.erase(v1.begin() + k);
							}
						}
					}
					for(int j = 0; j < 2; ++j)
					{
						for(int k = 0; k < v2.size(); ++k)
						{
							if(v2[k].first == player2.onePair_Value)
							{
								v2.erase(v2.begin() + k);
							}
						}
					}
					for(int j = 0; j < v1.size(); ++j)
					{
						for(int k = j + 1; k < v1.size(); ++k)
						{
							if(v1[k].first > v1[j].first);
							{
								swap(v1[k], v1[j]);
							}
						}
					}
					for(int j = 0; j < v2.size(); ++j)
					{
						for(int k = j + 1; k < v2.size(); ++k)
						{
							if(v2[k].first > v2[j].first);
							{
								swap(v2[k], v2[j]);
							}
						}
					}
					for(int i = 0; i < 3; ++i)
					{
						if(v1[i].first > v2[i].first)
						{
							++winner1;
							break;
						}
					}
					break;
				}
				case 0: {
					player1.sort();
					player2.sort();
					for(int j = 0; j < 5; ++j)
					{
						if(player1.hand[j].first > player2.hand[j].first)
						{
							++winner1;
							break;
						}
					}
					break;
				}
			}
		}
	}
	
	f.close();

	cout << winner1 << endl;

	return 0;
}
