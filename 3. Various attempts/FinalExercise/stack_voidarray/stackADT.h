#pragma once
#include <stdbool.h>
typedef struct node {
	void** nodes;
	int size;
	int top;
	int count;
}STACK;

STACK* createStack(int size);
void destroyStack(STACK* stack);
bool push(STACK* stack, void* dataPtr);
bool pop(STACK* stack);
bool stackTop(STACK* stack, void** dataPtr);
void catStack(STACK* a, STACK* b);