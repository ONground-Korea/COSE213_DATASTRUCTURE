#include "stackADT.h"

STACK* createStack()
{
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    if (stack == NULL)
        return NULL;

    stack->count = 0;
    stack->top = NULL;

    return stack;
}

void destroyStack(STACK* stack)
{
    // TODO
    if (stack)
    {
        STACK_NODE* del;
        while (stack->count > 0)
        {
            del = stack->top;
            stack->top = stack->top->next;
            free(del);
            stack->count--;
        }
        free(stack);
    }
}

void pushStack(STACK* stack, double data)
{
    // TODO
    STACK_NODE* newnode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    if (newnode == NULL) return;

    newnode->data = data;
    newnode->next = NULL;

    newnode->next = stack->top;
    stack->top = newnode;
    stack->count++;
}

void popStack(STACK* stack)
{
    // TODO
    if (stackCount(stack) <= 0)
        return;
    STACK_NODE* del = stack->top;
    stack->top = stack->top->next;
    free(del);
    stack->count--;
}

double* stackTop(STACK* stack)
{
    if (stack->count == 0)
        return NULL;

    return &(stack->top->data);
}

int stackCount(STACK* stack)
{
    return stack->count;
}
