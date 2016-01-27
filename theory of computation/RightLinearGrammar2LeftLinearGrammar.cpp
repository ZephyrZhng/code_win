#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

//for_each(begin,end, [&](type){})

// 如果S出现在产生是的右侧，则引进新变元S0，增加产生式S0->S
// 构造左线性文法
/*
	a 可以为空
	S->a 		S->a
	S->a Ai 	Ai->a
	Aj->a Ai 	Ai->Aj a
	Aj->a 		S->Aj a
*/

/*
	S->0A
	A->10A
	A->e
*/

/*
	S->A
	A->A10
	A->0
*/

class grammar
{
public:
	grammar() {
		ifstream f("E:\\document\\programs\\theory of computation\\RightLinearGrammar2LeftLinearGrammar.txt");

		f >> vn_size;
		for(int i = 0; i < vn_size; ++i) {
			char c;
			f >> c;
			vn.insert(c);
		}
		f >> vt_size;
		for(int i = 0; i < vt_size; ++i) {
			char c;
			f >> c;
			vt.insert(c);
		}

		f >> n;
		for(int i = 0; i < n; ++i) {
			string s;
			f >> s;
			g.push_back(s);
		}

		f.close();
	}

	void display() {
		for(auto& p: g) {
			cout << p << endl;
		}
	}

	void displayLeftLinearGrammar() {
		for(auto& p: leftLinearGrammar) {
			cout << p << endl;
		}
	}

	bool isTerminalStr(string::iterator beginIt, string::iterator endIt) {
		for(auto p = beginIt; p != endIt + 1; ++p) {
			if(find(vt.begin(), vt.end(), *p) == vt.end()) {
				return false;
			}
		}
		return true;
	}

	void rightLinearGrammarToLeftLinearGrammar() {
		for(auto p = g.begin(); p != g.end(); ++p) {
			auto borderIt = find((*p).begin(), (*p).end(), '-');
			//int  border = borderIt - (*p).begin();
			auto rightSideSIt = find(borderIt + 2, (*p).end(), 'S');
			if(rightSideSIt != (*p).end()) {
				leftLinearGrammar.insert("T->S");
			}
			if(*((*p).begin()) == 'S'
				&& (isTerminalStr(borderIt + 2, (*p).end() - 1)
					|| (*((*p).end() - 1) == 'e'
						&& borderIt + 2 == (*p).end() - 1))) {
				leftLinearGrammar.insert(*p);
			} else if(*((*p).begin()) == 'S'
						&& find(vn.begin(), vn.end(), *((*p).end() - 1)) != vn.end()
						&& (isTerminalStr(borderIt + 2, (*p).end() - 2)
							|| (find(vn.begin(), vn.end(), *(borderIt + 2)) != vn.end()
								&& borderIt + 2 == (*p).end() - 1))) {
				string newSentence;
				newSentence.push_back(*((*p).end() - 1));
				newSentence.push_back('-');
				newSentence.push_back('>');
				if(find(vn.begin(), vn.end(), *(borderIt + 2)) != vn.end()
					&& borderIt + 2 == (*p).end() - 1) {
					newSentence.push_back('e');
				} else {
					for(auto q = borderIt + 2; q != (*p).end() - 2 + 1; ++q) {
						newSentence.push_back(*q);
					}
				}
				leftLinearGrammar.insert(newSentence);
			} else if(find(vn.begin(), vn.end(), *((*p).begin())) != vn.end()
						&& find(vn.begin(), vn.end(), *((*p).end() - 1)) != vn.end()
						&& (isTerminalStr(borderIt + 2, (*p).end() - 2)
							|| (find(vn.begin(), vn.end(), *((*p).end() - 1)) != vn.end()
								&& borderIt + 2 == (*p).end() - 1))) {
				string newSentence;
				newSentence.push_back(*((*p).end() - 1));
				newSentence.push_back('-');
				newSentence.push_back('>');
				newSentence.push_back(*((*p).begin()));
				if(!(find(vn.begin(), vn.end(), *((*p).end() - 1)) != vn.end()
						&& borderIt + 2 == (*p).end() - 1)) {
					for(auto q = borderIt + 2; q != (*p).end() - 2 + 1; ++q) {
						newSentence.push_back(*q);
					}
				}
				leftLinearGrammar.insert(newSentence);
			} else if(find(vn.begin(), vn.end(), *((*p).begin())) != vn.end()
						&& (isTerminalStr(borderIt + 2, (*p).end() - 1)
							|| *((*p).end() - 1) == 'e')) {
				string newSentence;
				newSentence.push_back('S');
				newSentence.push_back('-');
				newSentence.push_back('>');
				newSentence.push_back(*((*p).begin()));
				if(!(*((*p).end() - 1) == 'e')) {
					for(auto q = borderIt + 2; q != (*p).end() - 1 + 1; ++q) {
						newSentence.push_back(*q);
					}
				}
				leftLinearGrammar.insert(newSentence);
			}
		}
	}

private:
	int n;
	int vn_size;
	int vt_size;
	vector<string> g;
	set<char> vn;
	set<char> vt;
	set<string> leftLinearGrammar;
};

int main()
{
	grammar g;

	g.display(); cout << "-----------------" << endl;
	g.rightLinearGrammarToLeftLinearGrammar();
	g.displayLeftLinearGrammar();

	return 0;
}