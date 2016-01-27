/*
A permutation is an ordered arrangement of objects. 
For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. 
If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. 
The lexicographic permutations of 0, 1 and 2 are:
012   021   102   120   201   210
What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*/
//2783915460
#include <iostream>
#include <algorithm>
using namespace std;

#define cnt 1000000

int main()
{
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int sum(0);
	int len = sizeof(arr) / sizeof(int);

	do
	{
		for(int i = 0; i < len; ++i)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
		++sum;
		if(sum == cnt)
		{
			break;
		}
	}while(next_permutation(arr, arr + len));
	//cout << sum << endl;

	return 0;
}