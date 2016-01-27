#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;

void display(const vector<int>& v)
{
	if(!v.size()) {cout << "phi" << endl; return;}
	for(int i = 0; i < v.size(); ++i) cout << v[i];
	cout << endl;
}

void P(int i, vector<int> A, vector<int>& B)
{
	if(i >= A.size()) display(B);
	else
	{
		B.push_back(A[i]);
		P(i + 1, A, B);
		B.erase(B.end() - 1);
		P(i + 1, A, B);
	}
}

int main()
{
	int arr[] = {1, 2, 3};
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));
	vector<int> _v;

	P(0, v, _v);

	return 0;
}