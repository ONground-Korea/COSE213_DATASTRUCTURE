#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define HEAP_UNIT 100

typedef struct heap {
	int* data;
	int size;
	int capacity;
} HEAP;

HEAP* heapCreate();
void heapDestroy(HEAP* heap);

bool heapInsert(HEAP* heap, int val);
int heapDelete(HEAP* heap);
void heapSort(int* data, int size);

int heapCount(HEAP* heap);
bool heapFull(HEAP* heap);
bool heapEmpty(HEAP* heap);
void heapTraverse(HEAP* heap);

// additional functions
void reheapUp(HEAP* heap, int pos);
void reheapDown(HEAP* heap, int pos);
void reheapUp_Iter(HEAP* heap, int pos);
void reheapDown_Iter(HEAP* heap, int pos);