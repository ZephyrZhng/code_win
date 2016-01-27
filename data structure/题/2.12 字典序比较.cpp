#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

int lexicographical_compare(const string& a, const string& b)
{
	int SHORT = a.size() <= b.size()? a.size(): b.size();
	for(int i = 0; i < SHORT; ++i)
	{
		if(a[i] > b[i]) return 1;
		if(a[i] < b[i]) return -1;
	}
	if(a.size() > b.size()) return 1;
	if(a.size() < b.size()) return -1;
	return 0;
}

int main()
{
	string a, b;
	cin >> a >> b;
	cout << lexicographical_compare(a, b) << endl;

	return 0;
}