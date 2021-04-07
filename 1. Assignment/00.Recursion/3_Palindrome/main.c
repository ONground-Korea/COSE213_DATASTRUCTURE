#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int getStrLength(const char* str, int length)
{
	length = 0;
	if (str[0] != '\0')
	{
		length = 1;
		length += getStrLength(str + length, length);
	}
	return length;
}
bool palindrome(const char* str, int start, int end)
{
	start = 0;
	if (end <= 0) return true;
	if (end > 0)
	{
		if (str[start] == str[end--] && palindrome(str + 1, start, --end))
		{
			return true;
		}
		else return false;
	}
	else return false;
}

int main()
{
	int n,start=0;
	printf("input number of words n : ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		char* str = (char*)malloc(sizeof(char)*1001);
		scanf("%s", str);
		printf("%s:", str);
		int length = 0;
		if (palindrome(str, start, getStrLength(str, length)-1))
			printf("The string is palindrome\n");
		else
			printf("The string is not palindrome\n");
		free(str);
	}
	
}