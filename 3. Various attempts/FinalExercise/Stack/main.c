#include "stackADT.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void catStackTest()
{
	char* data;

	////////////////////////////////////////
	// Fill stack A
	STACK* A = createStack();
	data = (char*)malloc(sizeof(char));
	*data = 'e';
	pushStack(A, data);
	data = (char*)malloc(sizeof(char));
	*data = 'd';
	pushStack(A, data);
	data = (char*)malloc(sizeof(char));
	*data = 'c';
	pushStack(A, data);

	////////////////////////////////////////
	// Fill stack B
	STACK* B = createStack();
	data = (char*)malloc(sizeof(char));
	*data = 'b';
	pushStack(B, data);
	data = (char*)malloc(sizeof(char));
	*data = 'a';
	pushStack(B, data);

	// concatenate
	catStack(A, B);

	////////////////////////////////////////
	// Print char values in Stack A
	//
	// EXPECTED OUTPUT:
	// a, b, c, d, e
	STACK_NODE* temp;
	while (stackTop(A) != NULL)
	{
		printf("%c", *(char*)stackTop(A));
		popStack(A);

		if (stackTop(A) != NULL)
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
	STACK* stack = createStack();
	int len = strlen(str);
	char* ch;
	for (int i = 0; i < len; i++)
	{
		switch (str[i]) {
		case '(': case'{': case '[':
			ch = (char*)malloc(sizeof(char));
			*ch = str[i];
			pushStack(stack, ch);
			break;

		case')':case'}':case']':
			if (stack->count <= 0)
				return false;
			else
			{
				char top = *(char*)stackTop(stack);
				
				if ((top == '(' && str[i] == ')') || (top == '{' && str[i] == '}') || (top == '[' && str[i] == ']'))
					popStack(stack);
				else
					return false;
			}
		}
	}

	if (stack->count > 0)
	{
		destroyStack(stack);
		return false;
	}
	if (stack->count == 0)
	{
		destroyStack(stack);
		return true;
	}
}

void braceCheckTest()
{
	const int numTestCase = 7;
	int i = 0;
	char str[7][100] = {
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