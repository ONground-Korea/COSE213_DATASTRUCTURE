#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibLoop(int n)
{
	int first = 1;
	int second = 1;
	int last = -1;
	if (n <2) return n;
	if (n == 2) return 1;
	for (int i = 3; i <= n; i++)
	{
		last = first + second;
		first = second;
		second = last;
	}
	return last;
}

int fibRecursion(int n)
{
	if (n < 2)return n;
	if (n == 2) return 1;
	return fibRecursion(n - 1) + fibRecursion(n - 2);
}

long long arr[60];
long long fibMemoization(long long* arr, int n)
{
	if (n < 2) return arr[n] = n;
	if (n == 2)return arr[n] = 1;
	if (arr[n]) return arr[n];
	else return arr[n] = fibMemoization(arr, n - 1) + fibMemoization(arr, n - 2);
}

int main()
{
	printf("Loop\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", fibLoop(i));
	}
	printf("\n");
	printf("Recursion\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", fibRecursion(i));
	}
	printf("\n");
	for (int i = 50; i < 60; i++)
	{
		printf("%lld\n", fibMemoization(arr, i));
	}
}