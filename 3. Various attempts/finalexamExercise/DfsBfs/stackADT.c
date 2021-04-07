#include "stackADT.h"
#include <string.h>
#include <stdlib.h>
STACK* createStack()
{
    // TODO
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    if (stack == NULL) return NULL;

    stack->count = 0;
    stack->top = NULL;
    return stack;
}

void destroyStack(STACK* stack)
{
    // TODO
    STACK_NODE* destroy;
    if (stack)
    {
        while (stack->top != NULL)
        {
            free(stack->top->dataPtr);
            destroy = stack->top;
            stack->top = destroy->link;
            free(destroy);
        }
        free(stack);
    }
}

void pushStack(STACK* stack, void* dataInPtr)
{
    // TODO
    // Use linked list
    STACK_NODE* newnode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    newnode->dataPtr = dataInPtr;
    newnode->link = stack->top;
    stack->top = newnode;
    stack->count++;
}

void popStack(STACK* stack)
{
    // TODO
    if (stack->count <= 0) return;
    STACK_NODE* del = stack->top;
    stack->top = del->link;
    free(del);
    stack->count--;
}

void* stackTop(STACK* stack)
{
    // TODO
    if (stack->count <= 0) return NULL;
    return stack->top->dataPtr;
}

void catStack(STACK* a, STACK* b)
{
    // TODO
    STACK* temp = createStack();
    while (b->top != NULL)
    {
        pushStack(temp, stackTop(b));
        popStack(b);
    }
    destroyStack(b);
    while (temp->top != NULL)
    {
        pushStack(a, stackTop(temp));
        popStack(temp);
    }
    destroyStack(temp);
}