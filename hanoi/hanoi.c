#include <stdio.h>/* ��ŵ�� */

int main()
{
	void hanoi (int n, char one, char two, char three);

	int n;

	printf("input the number of diskes:\n");
	scanf("%d", &n);
	printf("the steps of moving %d diskes:\n", n);
	hanoi(n, 'A', 'B', 'C');
	return 0;
}

void hanoi(int n, char one, char two, char three)
{
	void move (char x, char y);

	if(n == 1)
	{
		move(one, three);
	}
	else
	{
		hanoi(n - 1, one, three, two);
		move(one, three);
		hanoi(n - 1, two, one, three);
	}
}

void move (char x, char y)
{
	printf("%c->%c\n", x, y);
}
