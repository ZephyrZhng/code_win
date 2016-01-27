/*
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, 
there are exactly three solutions for p = 120.
{20,48,52}, {24,45,51}, {30,40,50}
For which value of p <= 1000, is the number of solutions maximised?
*/
//840
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

const int upperlimit = 1000;

bool check(int a, int b, int c)
{
	if(a * a + b * b == c * c ||
		a * a + c * c == b * b ||
		b * b + c * c == a * a)
	{
		return true;
	}
	return false;
}

int main()
{
	vector<int> ans;
	for(int perimeter = 3; perimeter <= upperlimit; ++perimeter)
	{
		int cnt(0);
		cout << perimeter << ":" << endl;
		for(int i = 1; i <= perimeter - 2; ++i)
		{
			for(int j = 1; j <= perimeter - i - 1; ++j)
			{
				int k = perimeter - i - j;
				if(check(i, j, k))
				{
					++cnt;
					cout << "\t: " << i << " " << " " << j << " " << k << endl;
				}
			}
		}
		ans.push_back(cnt);
	}
	vector<int>::iterator it = max_element(ans.begin(), ans.end());
	cout << it - ans.begin() + 3 << ": " << *it << endl;

	return 0;
}