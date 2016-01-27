/*
project euler problem 5
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
//232792560
#include <iostream>
using namespace std;



const int begin = 1;
const int end = 20;

inline long long gcd(long long a, long long b)
{
	return b ? gcd(b, a % b) : a;
}
inline long long lcm(long long a, long long b)
{
	return a * b / gcd(a, b);
}

int main()
{
	int i;
	long long result;

	for(i = 2, result = 1; i <= end; result = lcm(result, i), ++i);
	cout << result << endl;

	return 0;
}