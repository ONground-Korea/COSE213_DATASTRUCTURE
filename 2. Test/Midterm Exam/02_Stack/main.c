#define _CRT_SECURE_NO_WARNINGS

#include "stackADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LENGTH	32

void printHeader(const char* title);
void testStackADT();
void testPostfix();

double postfixEvaluate(const char* strPostfix)
{
	// TODO
	STACK* stack = createStack();
	double rval;
	double lval;
	for (int i = 0; i < strlen(strPostfix); i++)
	{
		if (strPostfix[i] != '+' && strPostfix[i] != '-' && strPostfix[i] != '*' && strPostfix[i] != '/')
		{
			pushStack(stack, strPostfix[i] - '0');
		}
		else
		{
			if(stackCount(stack)>0) rval = *stackTop(stack);
			popStack(stack);
			if(stackCount(stack)>0) lval = *stackTop(stack);
			popStack(stack);
			if (strPostfix[i] == '+')
			{
				pushStack(stack, lval + rval);
			}
			if (strPostfix[i] == '-')
			{
				pushStack(stack, lval - rval);
			}
			if (strPostfix[i] == '*')
			{
				pushStack(stack, lval * rval);
			}
			if (strPostfix[i] == '/')
			{
				pushStack(stack, lval / rval);
			}
		}
	}
	double result = *stackTop(stack);
	destroyStack(stack);
	return result;
}

int main(void)
{
	printHeader("Stack Test");
	testStackADT();

	printHeader("Postfix Test");
	testPostfix();

	return 0;
}

void testStackADT()
{
	STACK* myStack = createStack();

	pushStack(myStack, 1);
	pushStack(myStack, 2);
	pushStack(myStack, 3);

	while (stackCount(myStack) != 0)
	{
		printf("%f ", *stackTop(myStack));
		popStack(myStack);
	}
	printf("\n");

	destroyStack(myStack);
}

void testPostfix()
{
	double expect[] = { 2, 9, 4, 4.5, 9 };
	char str[][MAX_STR_LENGTH] = {
		{"18+7-"},
		{"12*7+"},
		{"42/12*+"},
		{"19*92/-"},
		{"42*8-23*+3+"},
	};

	for (int i = 0; i < sizeof(expect) / sizeof(double); i++)
	{
		printf("Testcase %02d: %s\n", i + 1, str[i]);
		double result = postfixEvaluate(str[i]);
		if (expect[i] == result)
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR: (Expect: %f, Real: %f)\n", expect[i], result);
		}
	}
}

void printHeader(const char* title)
{
	printf("\n####################\n# %s\n", title);
}