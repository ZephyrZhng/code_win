#include "head.h"
int s()
{
	int i, sum;

	for(i = 1, sum = 0; i <= 10; ++i)
	{
		sum += fac(i);
	}
	return sum;	
}