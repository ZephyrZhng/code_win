/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; 
for example, the 5-digit number, 15234, is 1 through 5 pandigital.
The product 7254 is unusual, as the identity, 39  186 = 7254, 
containing multiplicand, multiplier, and product is 1 through 9 pandigital.
Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
*/
//45228
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct elem
{
	int multiplicand;
	int multiplier;
	int product;
};

void digit(int a, vector<int>& v)
{
	for(int aa = a; aa > 0; aa /= 10)
	{
		v.push_back(aa % 10);
	}
}

bool check(const vector<int>& v)
{
	for(int i = 1; i <= 9; ++i)
	{
		if(find(v.begin(), v.end(), i) == v.end())
		{
			return false;
		}
	}
	return true;
}

int main()
{
	vector<struct elem> ans;
	for(int i = 1; i <= 99; ++i)
	{
		for(int j = 100; j <= 9999; ++j)
		{
			int ij = i * j;
			vector<int> v;
			digit(i, v);
			digit(j, v);
			digit(ij, v);
			if(v.size() == 9 && check(v))
			{
				elem element = {i, j, ij};
				ans.push_back(element);
			}
		}
	}
	for(vector<elem>::iterator i = ans.begin(); i < ans.end(); ++i)
	{
		for(vector<elem>::iterator j = i + 1; j < ans.end(); ++j)
		{
			if((*i).product == (*j).product)
			{
				ans.erase(j);
			}
		}
	}
	long long sum(0);
	for(int i = 0; i < ans.size(); ++i)
	{
		sum += ans[i].product;
		cout << i + 1 << ": ";
		cout << ans[i].multiplicand << " * " << ans[i].multiplier << " = " << ans[i].product << endl;
	}
	cout << sum << endl;

	return 0;
}