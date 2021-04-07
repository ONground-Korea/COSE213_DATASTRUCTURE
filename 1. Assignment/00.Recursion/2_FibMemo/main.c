#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
long long arr[1001];
long long fibMemoization(long long* arr, int n)
{
	if (n == 0) return 0;
	else if (n == 1 || n == 2) return 1;
	else if (arr[n]) return arr[n];
	else return arr[n] = fibMemoization(arr,n - 1) + fibMemoization(arr,n - 2);
}
int main()
{
	printf(" Memoization::\n");
	for (int i = 50; i <= 59; i++)
	{
		printf(" %d: %lld\n", i, fibMemoization(arr,i));
	}
}