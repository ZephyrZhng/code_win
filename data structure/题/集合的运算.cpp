#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <set>
#include <string>
#include <stack>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

void display(const vector<int>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i];
	cout << endl;
}

void display(const set<int>& s)
{
	for(auto p = s.begin(); p != s.end(); ++p)
		cout << *p << " ";
}

int main()
{
	int arr1[] = {1, 3, 6, 7, 8, 9};
	int arr2[] = {2, 3, 4, 6, 7, 8};
	vector<int> v1(arr1, arr1 + sizeof(arr1) / sizeof(int));
	vector<int> v2(arr2, arr2 + sizeof(arr2) / sizeof(int));
	sort(v1.begin(), v1.end());
	display(v1);
	sort(v2.begin(), v2.end());
	display(v2);
	vector<int> ans;

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(ans, ans.begin()));
	display(ans); ans.clear();
	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(ans, ans.begin()));
	display(ans); ans.clear();
	set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(ans, ans.begin()));
	display(ans); ans.clear();
	set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), inserter(ans, ans.begin()));
	display(ans); ans.clear();

	/*set<int> sa;
	sa.insert(1);
	sa.insert(3);
	sa.insert(6);
	sa.insert(7);
	sa.insert(8);
	sa.insert(9);
	set<int> sb;
	sa.insert(2);
	sa.insert(3);
	sa.insert(4);
	sa.insert(6);
	sa.insert(7);
	sa.insert(8);
	set<int> rlt;
	set_union(sa.begin(), sa.end(), sb.begin(), sb.end(), inserter(rlt, rlt.begin()));
	display(rlt); rlt.clear();*/

	return 0;
}