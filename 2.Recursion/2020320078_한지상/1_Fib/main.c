#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibLoop(int n)
{
	int first = 1;
	int second = 1;
	int last = -1;
	if (n == 0) return 0;
	else if (n == 1 || n == 2) return 1;
	else
	{
		for (int i = 3; i <= n; i++)
		{
			last = first + second;
			first = second;
			second = last;
		}
		return last;
	}
}
int fibRecursion(int n)
{
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return fibRecursion(n - 1) + fibRecursion(n - 2);
}

int main()
{
	printf("Loop::\n");
	for (int i = 0; i <= 9; i++)
	{
		printf(" %d : %d\n", i,fibLoop(i));
	}
	printf("--------------------\n");
	printf("Recursion::\n");
	for (int i = 0; i <= 9; i++)
	{
		printf(" %d : %d\n", i,fibRecursion(i));
	}
}