#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
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
#include <functional>
#include <cassert>
using namespace std;

class MinHeap
{
public:
	MinHeap();
	~MinHeap(){}
	void insert(int x);
	int removemin();
private:
	vector<int> heap;
};

void min_down(int start, vector<int>& heap)
{
	int i = start, j = 2 * i + 1, temp = heap[start];
	while(j <= heap.size() - 1)
	{
		if(j < heap.size() - 1 && heap[j] > heap[j + 1]) ++j;
		if(temp <= heap[j]) break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

void min_up(int start, vector<int>& heap)
{
	int j = start, i = (j - 1) / 2, temp = heap[start];
	while(j >= 0)
	{
		if(heap[i] <= temp) break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

void MinHeap::insert(int x)
{
	heap.push_back(x);
	min_up(heap.size() - 1, heap);
}

int MinHeap::removemin()
{
	int returnval = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.erase(heap.end() - 1);
	min_down(0, heap);
	return returnval;
}

MinHeap::MinHeap()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\课程设计\\heap.txt");
	assert(input);

	int p;
	while(input >> p)
		heap.push_back(p);

	input.close();

	for(int i = (heap.size() - 2) / 2; i >= 0; --i)
		min_down(i, heap);
}

class MaxHeap
{
public:
	MaxHeap();
	~MaxHeap(){}
	void insert(int x);
	int removemin();
private:
	vector<int> heap;
};

void max_down(int start, vector<int>& heap)
{
	int i = start, j = 2 * i + 1, temp = heap[start];
	while(j <= heap.size() - 1)
	{
		if(j < heap.size() - 1 && heap[j] < heap[j + 1]) ++j;
		if(temp >= heap[j]) break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

void max_up(int start, vector<int>& heap)
{
	int j = start, i = (j - 1) / 2, temp = heap[start];
	while(j >= 0)
	{
		if(heap[i] >= temp) break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

void MaxHeap::insert(int x)
{
	heap.push_back(x);
	max_up(heap.size() - 1, heap);
}

int MaxHeap::removemin()
{
	int returnval = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.erase(heap.end() - 1);
	max_down(0, heap);
	return returnval;
}

MaxHeap::MaxHeap()
{
	ifstream input("E:\\重要文档\\programs\\data structure\\课程设计\\heap.txt");
	assert(input);

	int p;
	while(input >> p)
		heap.push_back(p);

	input.close();

	for(int i = (heap.size() - 2) / 2; i >= 0; --i)
		max_down(i, heap);
}

int main()
{
	MinHeap minheap;
	MaxHeap maxheap;
	return 0;
}