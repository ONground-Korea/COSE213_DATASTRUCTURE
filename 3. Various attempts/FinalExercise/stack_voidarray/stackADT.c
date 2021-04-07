#include "stackADT.h"
#include <stdio.h>
#include <stdlib.h>

STACK* createStack(int size)
{
	STACK* stack = (STACK*)malloc(sizeof(STACK));
	if (stack == NULL) return NULL;

	stack->count = 0;
	stack->size = size;
	stack->top = -1;
	stack->nodes = (void**)malloc(sizeof(void*) * size);
	if (stack->nodes == NULL) return NULL;
	return stack;
}
void destroyStack(STACK* stack)
{
	if (stack)
	{
		free(stack->nodes);
		free(stack);
	}
}
bool push(STACK* stack, void* dataPtr)
{
	if (stack->count >= stack->size)
		return false;

	stack->top++;
	stack->nodes[stack->top] = dataPtr;
	stack->count++;
	return true;
}
bool pop(STACK* stack)
{
	if (stack->count == 0)
		return false;

	stack->top--;
	stack->count--;
	return true;
}
bool stackTop(STACK* stack, void** dataPtr)
{
	if (stack->count <= 0)
		return false;

	*dataPtr = stack->nodes[stack->top];
	return true;
}
void catStack(STACK* a, STACK* b)
{
	STACK* temp = createStack(b->size);
	void* data;
	while (b->count > 0)
	{
		if (stackTop(b, &data))
		{
			push(temp, data);
			pop(b);
		}
	}
	destroyStack(b);
	while (temp->count > 0)
	{
		if (stackTop(temp, &data))
		{
			push(a, data);
			pop(temp);
		}
	}
	destroyStack(temp);
}