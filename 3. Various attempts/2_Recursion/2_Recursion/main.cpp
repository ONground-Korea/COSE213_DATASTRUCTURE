#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

int getStrLength(const char* str, int length);
bool palindrome(const char* str, int start, int end);

int main()
{
	char arr[1000];
	int n;
	printf("문자 개수를 입력하세요 : ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", arr);
		printf("%s : ", arr);
		if (palindrome(arr, 0, getStrLength(arr, 0)-1))
			printf("The string is palindrome\n");
		else
			printf("The string is not palindrome\n");
	}
}

int getStrLength(const char* str, int length)
{
	if (str[0] == '\0') return length;
	length = getStrLength(str + 1, ++length);
}

bool palindrome(const char* str, int start, int end)
{
	if (str[0] == '\0' || end <= 0) return true;
	if (str[0] != str[end]) return false;
	else
	{
		if (palindrome(str + 1, 0, end-2))
			return true;
	}

}