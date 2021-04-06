#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "heapADT.h"

HEAP* heapCreate()
{
	// TODO
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	if (heap == NULL) return NULL;

	heap->capacity = HEAP_UNIT;
	heap->size = 0;
	heap->data = (int*)malloc(sizeof(int) * heap->capacity);
	if (heap->data == NULL) return NULL;

	return heap;
}

void heapDestroy(HEAP* heap)
{
	// TODO
	if (heap)
	{
		free(heap->data);
		free(heap);
	}
}

bool heapInsert(HEAP* heap, int val)
{
	// TODO
	if (heapFull(heap))
		return false;

	heap->data[heap->size++] = val;
	reheapUp(heap, heap->size - 1);
	return true;
}

int heapDelete(HEAP* heap)
{
	// TODO
	if (heapEmpty(heap))
		return -1;

	int dataOut = heap->data[0];
	heap->data[0] = heap->data[--heap->size];
	reheapDown(heap, 0);
	return dataOut;
}

int heapCount(HEAP* heap)
{
	return heap->size;
}

bool heapFull(HEAP* heap)
{
	return heap->size >= heap->capacity;
}

bool heapEmpty(HEAP* heap)
{
	return heap->size == 0;
}

void heapTraverse(HEAP* heap)
{
	// TODO
	for (int i = 0; i < heap->size; i++)
		printf("%d ", heap->data[i]);
	printf("\n");
}

// additional functions
void reheapUp(HEAP* heap, int pos)
{
	// TODO
	int parentIdx = 0;
	if (pos <= 0 || pos >= heap->size)
		return;

	parentIdx = (pos - 1) / 2;
	if (heap->data[pos] > heap->data[parentIdx])
	{
		int temp = heap->data[pos];
		heap->data[pos] = heap->data[parentIdx];
		heap->data[parentIdx] = temp;
		reheapUp(heap, parentIdx);
	}
}

void reheapDown(HEAP* heap, int pos)
{
	// TODO
	if (pos < 0 || pos >= heap->size)
		return;

	if (pos * 2 + 1 < heap->size)
	{
		int maxChild = pos * 2 + 1;
		if (maxChild + 1 < heap->size && heap->data[maxChild] < heap->data[maxChild + 1])
			maxChild++;

		if (heap->data[pos] < heap->data[maxChild])
		{
			int temp = heap->data[pos];
			heap->data[pos] = heap->data[maxChild];
			heap->data[maxChild] = temp;
			reheapDown(heap, maxChild);
		}

	}
}
