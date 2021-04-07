#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LENGTH	32

void testPalindromeLoop();
void testPalindromeRecur();
void printHeader(const char* title);

bool isPalindromeLoop(const char* str, int length)
{
	// TODO
	for (int i = 0; i < length; i++)
	{
		if (length <= 0 || i >= length - 1 - i)
			return true;
		if (str[i] != str[length - 1 - i])
			return false;
	}
	return true;
}

bool isPalindromeRecur(const char* str, int length, int pos)
{
	// TODO
	if (length <= 1)
		return true;
	if (pos >= length)
		return true;

	if (str[pos] == str[length - 1 - pos] && isPalindromeRecur(str, length, ++pos))
		return true;
	else
		return false;


}

int main()
{
	printHeader("Palindrome Loop Test");
	testPalindromeLoop();

	printHeader("Palindrome Recursion Test");
	testPalindromeRecur();

	return 0;
}

void testPalindromeLoop()
{
	bool expect[] = { true, true, true, true, false, false, false };
	char str[][MAX_STR_LENGTH] = { "abccba", "abcba", "aba", "a", "ab", "abc", "abca" };

	for (int i = 0; i < sizeof(str) / MAX_STR_LENGTH; ++i)
	{
		printf("Testcase %02d: %s\n", i + 1, str[i]);
		bool result = isPalindromeLoop(str[i], strlen(str[i]));
		if (expect[i] == result)
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR (Expect: %s, Real: %s)\n", expect[i] ? "true" : "false", result ? "true" : "false");
		}
	}
}

void testPalindromeRecur()
{
	bool expect[] = { true, true, true, true, false, false, false };
	char str[][MAX_STR_LENGTH] = { "abccba", "abcba", "aba", "a", "ab", "abc", "abca" };

	for (int i = 0; i < sizeof(str) / MAX_STR_LENGTH; ++i)
	{
		printf("Testcase %02d: %s\n", i + 1, str[i]);
		bool result = isPalindromeRecur(str[i], strlen(str[i]), 0);
		if (expect[i] == result)
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR (Expect: %s, Real: %s)\n", expect[i] ? "true" : "false", result ? "true" : "false");
		}
	}
}

void printHeader(const char* title)
{
	printf("\n####################\n# %s\n", title);
}

/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int compare(void* ptr1, void* ptr2);
int int_compare(void* ptr1, void* ptr2)
{
	if (*(int*)ptr1 >= *(int*)ptr2)
		return 1;
	else
		return -1;
}
void* larger(void* dataPtr1, void* dataPtr2, int(*ptrToCmpFun)(void*, void*))
{
	if ((*ptrToCmpFun)(dataPtr1, dataPtr2) > 0)
		return dataPtr1;
	else
		return dataPtr2;
}
int main()
{
	int i = 7;
	int j = 8;
	int lrg = *(int*)larger(&i, &j, int_compare);
}
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
		if (palindrome(str + 1, 0, end - 2))
			return true;
	}

}
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	if (a == 0)
		return b;
	return gcd(b, a % b);
}
*/

/*int preToPostFix(char* preFixIn, char* postFix) // return value: length of converted expression
{
	char op[2]; // operator
	int p = 0;
	// base case
	if (strchr("+-*//*", preFixIn[0]) == NULL) {
		postFix[0] = preFixIn[0];
		postFix[1] = '\0';
		return strlen(postFix);
	}
	// general case
	op[0] = preFixIn[p++];
	op[1] = '\0';
	p += preToPostFix(preFixIn + p, postFix);
	p += preToPostFix(preFixIn + p, postFix + strlen(postFix));
	strcat(postFix, op);
	// return length of current sub-expression
	return strlen(postFix);
} // preToPostFix

int count(int x)
{

	if (x == 1)
		return 1;
	if (x == 2)
		return 3;
	else
		return (2 * count(x - 1) + 1);
}
void hanoi(int n, int from1, int tmp, int to)
{
	if (n == 1)
		printf("%d %d", from1, to);
	else
	{
		hanoi(n - 1, from1, to, tmp);
		printf("%d %d", from1, to);
		hanoi(n - 1, tmp, from1, to);
	}
}
*/
			
/*int main()
{
	int N;
	scanf("%d", &N);
	hanoi(N, 1, 2, 3);
	int n, start = 0;
	printf("input number of words n : ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		char* str = (char*)malloc(sizeof(char) * 1001);
		scanf("%s", str);
		printf("%s: ", str);
		int length = 0;
		if (palindrome(str, start, getStrLength(str, length) - 1))
			printf("The string is palindrome\n");
		else
			printf("The string is not palindrome\n");
		free(str);
	}
}*/