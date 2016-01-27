/*
The number, 1406357289, is a 0 to 9 pandigital number 
because it is made up of each of the digits 0 to 9 in some order, 
but it also has a rather interesting sub-string divisibility property.
Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:
d2d3d4=406 is divisible by 2 
d3d4d5=063 is divisible by 3 
d4d5d6=635 is divisible by 5 
d5d6d7=357 is divisible by 7 
d6d7d8=572 is divisible by 11 
d7d8d9=728 is divisible by 13 
d8d9d10=289 is divisible by 17 
Find the sum of all 0 to 9 pandigital numbers with this property.
*/
//16695334890
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>
using namespace std;

int arr[] = {2, 3, 5, 7, 11, 13, 17};
vector<int> data(arr, arr + sizeof(arr) / sizeof(int));

long long vector2int(const vector<int>& v)
{
	long long ans(0);
	for(int i = 0; i < v.size(); ++i)
	{
		ans *= 10;
		ans += v[i];
	}
	return ans;
}

bool check_property(vector<int>& v)
{
	for(vector<int>::iterator it = v.begin() + 1; it != v.end() - 2; ++it)
	{
		int cnt = it - v.begin() - 1;
		vector<int> vsub(3);
		copy(it, it + 3, vsub.begin());
		if(vector2int(vsub) % data[cnt])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	
	long long sum(0);
	vector<int> v;

	for(int i = 0; i <= 9; ++i)
	{
		v.push_back(i);
	}
	do 
	{
		if(v[0] == 0)
		{
			continue;
		}
		if(check_property(v))
		{
			long long num = vector2int(v);
			sum += num;
			cout << num << endl;
		}
	}while(next_permutation(v.begin(), v.begin() + v.size()));
	cout << sum << endl;

	return 0;
}