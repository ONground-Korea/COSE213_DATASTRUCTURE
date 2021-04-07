#pragma once
#include <stdbool.h>
typedef struct node {
	void** nodes;
	int size;
	int top;
	int count;
}Stack;

Stack* createStack(int size);
void destroyStack(Stack* stack);
bool push(Stack* stack, void* dataPtr);
bool pop(Stack* stack);
bool stackTop(Stack* stack, void** dataPtr);
void catStack(Stack* a, Stack* b);