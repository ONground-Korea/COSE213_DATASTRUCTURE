#define _CRT_SECURE_NO_WARNINGS

#include "stackADT.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 100

void catStackTest()
{
	char* data;

	////////////////////////////////////////
	// Fill stack A
	Stack* A = createStack(SIZE);
	data = (char*)malloc(sizeof(char));
	*data = 'e';
	push(A, data);
	data = (char*)malloc(sizeof(char));
	*data = 'd';
	push(A, data);
	data = (char*)malloc(sizeof(char));
	*data = 'c';
	push(A, data);

	////////////////////////////////////////
	// Fill stack B
	Stack* B = createStack(SIZE);
	data = (char*)malloc(sizeof(char));
	*data = 'b';
	push(B, data);
	data = (char*)malloc(sizeof(char));
	*data = 'a';
	push(B, data);

	// concatenate
	catStack(A, B);

	////////////////////////////////////////
	// Print char values in Stack A
	//
	// EXPECTED OUTPUT:
	// a, b, c, d, e

	void* ch;
	while (stackTop(A, &ch))
	{
		printf("%c", *(char*)ch);
		pop(A);

		if (stackTop(A, &ch))
		{
			printf(", ");
		}
	}
	printf("\n");
	destroyStack(A);
}

bool braceCheck(const char* str)
{
	// TODO
	Stack* stack = createStack(SIZE);
	char* ch;
	int length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		switch (str[i]) {
		case '(': case '{': case '[':
			ch = (char*)malloc(sizeof(char));
			*ch = str[i];
			push(stack, ch);
			break;
		case ')': case '}': case ']':
			if (stack->count <= 0) return false;
			else
			{
				void* data;
				char top;
				if (stackTop(stack, &data))
					top = *(char*)data;
				//char top = *(char*)(stackTop(stack));
				if ((str[i] == ')' && top == '(') || (str[i] == '}' && top == '{') || (str[i] == ']' && top == '['))
				{
					pop(stack);
				}
				else return false;
			}
			break;
		}

	}
	if (stack->count > 0)
	{
		destroyStack(stack);
		return false;
	}
	destroyStack(stack);
	return true;
}

void braceCheckTest()
{
	const int numTestCase = 7;
	int i = 0;
	char str[numTestCase][100] = {
		{"So when I die (the [first] I will see in (heaven) is a score list)."},
		{"[ first in ] ( first out )."},
		{"Half Moon tonight (At least it is better than no Moon at all]."},
		{"A rope may form )( a trail in a maze."},
		{"Help( I[m being held prisoner in a fortune cookie factory)]."},
		{"([ (([( [ ] ) ( ) (( ))] )) ])."},
		{"."}
	};

	for (i = 0; i < numTestCase; ++i)
	{
		if (braceCheck(str[i]))
		{
			printf("yes\n");
		}
		else
		{
			printf("no\n");
		}
	}
}

int main(void)
{
	catStackTest();

	braceCheckTest();

	return 0;
}