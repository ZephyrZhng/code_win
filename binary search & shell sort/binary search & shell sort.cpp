#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

template<class T>
void display(const vector<T>& v)
{
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << "\t";
	cout << endl;
}

int BinSearch (vector<int> v, int x)
{
	int low(0), high(v.size() - 1), mid;

	while(low <= high)
	{
		mid = (low + high) / 2;
		if(x > v[mid])
			low = mid + 1;
		else if(x < v[mid])
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

int BinSearch(int low, int high, int key, const vector<int>& v)
{
	if(low == high)
	{
		if(v[low] == key) return low;
		else return -1;
	}
	else
	{
		int mid = (low + high) / 2;
		if(key > v[low]) return BinSearch(mid + 1, high, key, v);
		else if(key < v[mid]) return BinSearch(low, mid - 1, key, v);
		else return mid;
	}
}

template<class T>
void ShellSort (vector<T>& v)
{
	for(int gap = v.size() / 2; gap > 0; gap /= 2)
		for(int i = gap; i < v.size(); ++i)
			for(int j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
				swap(v[j], v[j + gap]);
}

int main()
{
	int arr[] = {3, 5, 1, 7, 4};
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));

	ShellSort(v);
	display(v);
	cout << BinSearch(v, 5) << endl;
	cout << BinSearch(0, v.size() - 1, 5, v) << endl;

	return 0;
}