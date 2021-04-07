#include "stackADT.h"

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
    if (stack)
    {
        STACK_NODE* del;
        while (stack->count > 0)
        {
            free(stack->top->dataPtr);
            del = stack->top;
            stack->top = stack->top->link;
            free(del);
            stack->count--;
        }
        free(stack);
    }
}

void pushStack(STACK* stack, void* dataInPtr)
{
    // TODO
    // Use linked list
    STACK_NODE* newnode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    if (newnode == NULL)return NULL;

    newnode->dataPtr = dataInPtr;
    newnode->link = NULL;

    newnode->link = stack->top;
    stack->top = newnode;

    stack->count++;
}

void popStack(STACK* stack)
{
    // TODO
    if (stack->count <= 0)
        return;
    STACK_NODE* del = stack->top;
    stack->top = stack->top->link;
    free(del->dataPtr);
    free(del);
    stack->count--;
}

void* stackTop(STACK* stack)
{
    // TODO
    if (stack->count <= 0)return NULL;
    return stack->top->dataPtr;
}

void catStack(STACK* a, STACK* b)
{
    // TODO
    STACK* c = createStack();
    //char* temp;
    void** tep;
    while (b->count>0)
    {
        //temp = (char*)malloc(sizeof(char));
       // *temp = *(char*)stackTop(b);
        tep = (void**)malloc(sizeof(void*));
        *tep = *(char*)stackTop(b);
        pushStack(c, tep);
        popStack(b);
    }
    destroyStack(b);
    while (c->count>0)
    {
        //temp = (char*)malloc(sizeof(char));
        //*temp = *(char*)stackTop(c);
        tep = (void**)malloc(sizeof(void*));
        *tep = *(char*)stackTop(c);
        pushStack(a, tep);
        popStack(c);
    }
    destroyStack(c);
}