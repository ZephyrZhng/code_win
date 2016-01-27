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

// A00000000
// B1010101101100101110111010111001101101101101000
// C10110

// M = (K, Sigma, Tau, delta, q0, B, F)

class code
{
public:
	code();
	void displaySrcCode();
	void displayCode();
	void encode();
	int B;
	int F;
	int K;
	int Gamma;
	vector<char> CODE;
	vector<string> stateSet;
	vector<string> characterSet;
private:
	vector< vector<string> > srcCODE;
	int programLen;
};

code::code()
{
	ifstream codeFile("E:\\document\\programs\\theory of computation\\code.txt");
	codeFile >> K;
	stateSet.resize(K);
	for(int i = 0; i < K; ++i)
	{
		codeFile >> stateSet[i];
	}
	codeFile >> Gamma;
	characterSet.resize(Gamma);
	for(int i = 0; i < Gamma; ++i)
	{
		codeFile >> characterSet[i];
	}
	codeFile >> programLen;
	srcCODE.resize(programLen);
	for(int i = 0; i < programLen; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			string s;
			codeFile >> s;
			srcCODE[i].push_back(s);
		}
	}

	codeFile.close();

	B = characterSet.size();
	F = characterSet.size();
}

void code::displaySrcCode()
{
	for(int i = 0; i < srcCODE.size(); ++i)
	{
		for(auto& j: srcCODE[i])
		{
			cout << j << " ";
		}
		cout << endl;
	}
}

void code::displayCode()
{
	for(auto& i: CODE)
	{
		cout << i;
	}
	cout << endl;
}

void code::encode()
{
	for(int i = 0; i < srcCODE.size(); ++i)
	{
		int statePos;
		int characterPos;

		statePos = find(stateSet.begin(), stateSet.end(), srcCODE[i][0]) - stateSet.begin();
		for(int j = 0; j < statePos + 1; ++j)
		{
			CODE.push_back('1');
		}
		CODE.push_back('0');

		characterPos = find(characterSet.begin(), characterSet.end(), srcCODE[i][1]) - characterSet.begin();
		for(int j = 0; j < characterPos + 1; ++j)
		{
			CODE.push_back('1');
		}
		CODE.push_back('0');

		characterPos = find(characterSet.begin(), characterSet.end(), srcCODE[i][2]) - characterSet.begin();
		for(int j = 0; j < characterPos + 1; ++j)
		{
			CODE.push_back('1');
		}
		CODE.push_back('0');

		if(srcCODE[i][3] == "L")
		{
			CODE.push_back('1');
		}
		else if(srcCODE[i][3] == "R")
		{
			CODE.push_back('1');
			CODE.push_back('1');
		}
		else
		{
			CODE.push_back('1');
			CODE.push_back('1');
			CODE.push_back('1');
		}
		CODE.push_back('0');

		statePos = find(stateSet.begin(), stateSet.end(), srcCODE[i][4]) - stateSet.begin();
		for(int j = 0; j < statePos + 1; ++j)
		{
			CODE.push_back('1');
		}
		CODE.push_back('0');
		CODE.push_back('0');
	}
	CODE.push_back('0');
}

class utm
{
public:
	utm(code _CODE, string inputString);
	void display();
	bool s0();
	bool s1();
	bool s2();
	bool s3();
	bool s4();
	bool s5();
	bool s6();
	bool s7();
	void simulate();
	int getFragmentLen(int segment, int offset);
	void copy(int destSegment, int destOffset, int srcSegment, int srcOffset);
	int searchSubSeq(const vector<char>& subSeq, int destSegment);
	int moveTag(int segment, char tag, int direction);
private:
	vector< vector<char> > tape;
	bool halt;
	code CODE;
	string inputString;
};

utm::utm(code _CODE, string _inputString): CODE(_CODE), inputString(_inputString)
{
	CODE.encode();

	vector<char> A(CODE.K + CODE.Gamma + 2, '0');
	vector<char> B(CODE.CODE);
	vector<char> C;

	for(auto p = inputString.begin(); p != inputString.end(); ++p)
	{
		string tmpString;
		tmpString.push_back(*p);
		int characterPos = find(CODE.characterSet.begin(), CODE.characterSet.end(), tmpString) - CODE.characterSet.begin();
		for(int j = 0; j < characterPos + 1; ++j)
		{
			C.push_back('1');
		}
		C.push_back('0');
	}

	A.insert(A.begin(), 'A');
	B.insert(B.begin(), 'B');
	C.insert(C.begin(), 'C');

	tape.push_back(A);
	tape.push_back(B);
	tape.push_back(C);

	halt = 0;

	cout << "source code: " << endl; CODE.displaySrcCode();
	cout << "encoded code: "; CODE.displayCode();
	cout << "input string: " << inputString << endl;
}

void utm::display()
{
	for(int i = 0; i < 3; ++i)
	{
		for(auto& j: tape[i])
		{
			cout << j;
		}
	}
	cout << endl;
}

int utm::getFragmentLen(int segment, int offset)
{
	return find(tape[segment].begin() + offset + 1, tape[segment].end(), '0') - tape[segment].begin() - offset - 1;
}

void utm::copy(int destSegment, int destOffset, int srcSegment, int srcOffset)
{
	int fragmentLen = getFragmentLen(srcSegment, srcOffset);
	for(int i = 0; i < fragmentLen; ++i)
	{
		tape[destSegment][destOffset + i + 1] = '1';
	}
}

int utm::searchSubSeq(const vector<char>& subSeq, int destSegment)
{
	bool flag = 1;
	for(int i = 0; i < tape[destSegment].size() - 2; )
	{
		if(tape[destSegment][i] == '0' && tape[destSegment][i + 1] == '0'
			&& tape[destSegment][i + 2] != '0')
		{
			i += 2;
			flag = 1;
		}
		if(tape[destSegment][i] == 'B')
		{
			++i;
			flag = 1;
		}
		if(flag)
		{
			bool matched = true;
			for(int j = 0; j < subSeq.size(); ++j)
			{
				if(tape[destSegment][j + i] != subSeq[j])
				{
					matched = false;
					break;
				}
			}
			if(matched && tape[destSegment][i + subSeq.size()] == '0')
			{
				return i;
			}
			else
			{
				++i;
				flag = 0;
			}
		}
		else
		{
			++i;
		}
	}
	return -1;
}

int utm::moveTag(int segment, char tag, int direction)
{
	// direction: 1. left 2. right 3. stay
	// return:
	// -1. leave from leaft
	// 0.  don't leave
	// 1.  leave from right
	switch(direction)
	{
		case 1: {
			int curTagPos = find(tape[segment].begin(), tape[segment].end(), tag) - tape[segment].begin();
			if(curTagPos == 0)
			{
				return -1;
			}
			int fragmentLen;
			for(int i = curTagPos - 1; i >= 0; --i)
			{
				if(tape[segment][i] == '0')
				{
					fragmentLen = curTagPos - i - 1;
					break;
				}
			}
			tape[segment][curTagPos - fragmentLen - 1] = tag;
			tape[segment][curTagPos] = '0';
			return 0;
		}
		case 2: {
			int curTagPos = find(tape[segment].begin(), tape[segment].end(), tag) - tape[segment].begin();
			tape[segment][curTagPos + getFragmentLen(segment, curTagPos) + 1] = tag;
			tape[segment][curTagPos] = '0';
			return 0;
		}
		case 3: {
			return 0;
		}
	}
}

bool utm::s0()
{
	cout << "s0: "; display();
	return halt;
}

bool utm::s1() 
{
	auto p = find(tape[1].begin(), tape[1].end(), 'E');
	*p = '0';
	int srcOffset = (p == tape[1].end())? 0: p - tape[1].begin();
	copy(0, 0, 1, srcOffset);
	int fragmentLen = getFragmentLen(1, srcOffset);
	tape[0][fragmentLen + 1] = 'D';
	cout << "s1: "; display();
	return halt;
}

bool utm::s2()
{
	copy(0, find(tape[0].begin(), tape[0].end(), 'D') - tape[0].begin(),
		2, find(tape[2].begin(), tape[2].end(), 'C') - tape[2].begin());
	cout << "s2: "; display();
	return halt;
}

bool utm::s3()
{
	tape[0][find(tape[0].begin(), tape[0].end(), 'D') - tape[0].begin()] = '0';
	cout << "s3: "; display();
	return halt;
}

bool utm::s4()
{
	vector<char> subSeq;
	int end;
	for(int i = tape[0].size() - 1; i > 0; --i)
	{
		if(tape[0][i] != '0')
		{
			end = i;
			break;
		}
	}
	for(int i = 1; i <= end; ++i)
	{
		subSeq.push_back(tape[0][i]);
	}
	if(searchSubSeq(subSeq, 1) == -1)
	{
		halt = 1;
	}
	else
	{
		tape[0][find(tape[0].begin(), tape[0].end(), '0') - tape[0].begin()] = 'D';
		tape[1][find(tape[1].begin() + searchSubSeq(subSeq, 1), tape[1].end(), '0') - tape[1].begin()] = 'E';
	}
	cout << "s4: "; display();
	return halt;
}

bool utm::s5()
{
	for(int i = 1; i < tape[0].size(); ++i)
	{
		tape[0][i] = '0';
	}
	moveTag(1, 'E', 2);
	cout << "s5: "; display();
	return halt;
}

bool utm::s6()
{
	int srcFragmentLen  = getFragmentLen(1, find(tape[1].begin(), tape[1].end(), 'E') - tape[1].begin());
	int destFragmentLen = getFragmentLen(2, find(tape[2].begin(), tape[2].end(), 'C') - tape[2].begin());
	if(destFragmentLen != srcFragmentLen)
	{
		int fragmentLenDifference = destFragmentLen - srcFragmentLen;
		if(fragmentLenDifference < 0)
		{
			for(int i = 0; i < fragmentLenDifference; ++i)
			{
				tape[2].insert(find(tape[2].begin(), tape[2].end(), 'C') + 1, '1');
			}
		}
		else
		{
			fragmentLenDifference *= -1;
			for(int i = 0; i < fragmentLenDifference; ++i)
			{
				tape[2].erase(find(tape[2].begin(), tape[2].end(), 'C') + 1);
			}
		}
	}
	moveTag(1, 'E', 2);
	cout << "s6: "; display();
	return halt;
}

bool utm::s7()
{
	int direction = getFragmentLen(1, find(tape[1].begin(), tape[1].end(), 'E') - tape[1].begin());
	int moveRlt = moveTag(2, 'C', direction);
	if(moveRlt == -1)
	{
		halt = 1;
	}
	if(tape[2][tape[2].size() - 1] == 'C')
	{
		for(int i = 0; i < CODE.B; ++i)
		{
			tape[2].push_back('1');
		}
		tape[2].push_back('0');
	}
	moveTag(1, 'E', 2);
	cout << "s7: "; display();
	if(getFragmentLen(1, find(tape[1].begin(), tape[1].end(), 'E') - tape[1].begin()) == CODE.F)
	{
		halt = 1;
	}
	return halt;
}

void utm::simulate()
{
	s0();
	while(!halt)
	{
		if(s1()) break;
		if(s2()) break;
		if(s3()) break;
		if(s4()) break;
		if(s5()) break;
		if(s6()) break;
		if(s7()) break;
	}
}

int main()
{
	code CODE;
	string inputString;

	char cmd = 'l';
	while(cmd == 'l')
	{
		system("cls");
		cout << "Please input your string:" << endl;
		cin >> inputString;
		utm UTM(CODE, inputString);
		UTM.simulate();
		cin >> cmd;
	}

	return 0;
}