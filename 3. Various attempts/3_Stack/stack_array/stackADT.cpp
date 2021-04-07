#include "stackADT.h"
#include <stdio.h>
#include <stdlib.h>

Stack* createStack(int size)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) return NULL;

	stack->size = size;
	stack->top = -1;
	stack->count = 0;
	stack->nodes = (void**)malloc(sizeof(void*)*size);
	if (stack->nodes == NULL) return NULL;
	return stack;
}

void destroyStack(Stack* stack)
{
	if (stack)
	{
		free(stack->nodes);
		free(stack);
	}
}
bool push(Stack* stack, void* dataPtr)
{
	if (stack->top >= stack->size - 1)
		return false;

	stack->top++;
	stack->count++;
	stack->nodes[stack->top] = dataPtr;
	return true;
}

bool pop(Stack* stack)
{
	if (stack->top < 0)
		return false;

	stack->top--;
	stack->count--;
	return true;
}

bool stackTop(Stack* stack, void** dataPtr)
{
	if (stack->top < 0)
		return false;

	*dataPtr = stack->nodes[stack->top];
	return true;
}

void catStack(Stack* a, Stack* b)
{
	Stack* temp = createStack(100);
	void* ch = NULL;
	while (b->top > -1)
	{
		if (stackTop(b, &ch))
		{
			push(temp, ch);
			pop(b);
		}
	}
	destroyStack(b);
	while (temp->top > -1)
	{
		if (stackTop(temp, &ch))
		{
			push(a, ch);
			pop(temp);
		}
	}
	destroyStack(temp);
}