#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;

long long akm1(int m, int n)
{
	if(!m) return n + 1;
	if(m && !n) return akm1(m - 1, 1);
	if(m && n) return akm1(m - 1, akm1(m, n - 1));
}

long long akm2(int m, int n)
{

}

int main()
{
	cout << akm1(2, 1) << endl;

	return 0;
}