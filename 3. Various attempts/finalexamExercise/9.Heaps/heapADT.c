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
	if (heapFull(heap)) return false;

	heap->data[heap->size++] = val;
	//reheapUp(heap, heap->size - 1);
	reheapUp_Iter(heap, heap->size - 1);
	return true;

	// 힙이 다 찼을 때 배열 크기 확장하는 버전
	/*
	if (heapFull(heap))
	{
		int* oData = heap->data;
		int* nData = (int*)realloc(heap->data, sizeof(int) * (heap->capacity + HEAP_UNIT));

		if (!nData)
		{
			heap->data = oData;
			return false;
		}
	}

	heap->data[(heap->size)] = val;
	reheapUp(heap, (heap->size)++);

	return true;
	*/
}

int heapDelete(HEAP* heap)
{
	// TODO
	if (heapEmpty(heap)) return -1;

	int dataOut = heap->data[0];
	heap->data[0] = heap->data[--heap->size];
	//reheapDown(heap, 0);
	reheapDown_Iter(heap, 0);
	return dataOut;
}

void heapSort(int* data, int size)
{
	HEAP* heap = heapCreate();

	for (int i = 0; i < size; i++)
		heapInsert(heap, data[i]);
	for (int i = size - 1; i >= 0; i--)
		data[i] = heapDelete(heap);

	heapDestroy(heap);
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
	if (heap)
	{
		for (int i = 0; i < heap->size; i++)
		{
			printf("%d ", heap->data[i]);
		}
	}
	printf("\n");
}

// additional functions
void reheapUp(HEAP* heap, int pos)
{
	// TODO
	if (pos <= 0 || pos >= heap->size) return;

	int parentIdx = (pos - 1) / 2;
	if (heap->data[parentIdx] < heap->data[pos])
	{
		int temp = heap->data[pos];
		heap->data[pos] = heap->data[parentIdx];
		heap->data[parentIdx] = temp;
		reheapUp(heap, parentIdx);
	}
}

void reheapUp_Iter(HEAP* heap, int pos)
{
	if (pos <= 0 || pos >= heap->size) return;

	int curData = heap->data[pos];
	int parentIdx = (pos - 1) / 2;
	while (pos > 0 && heap->data[parentIdx] < curData)
	{
		heap->data[pos] = heap->data[parentIdx];
		pos = parentIdx;
		parentIdx = (pos - 1) / 2;
	}
	heap->data[pos] = curData;
}

void reheapDown(HEAP* heap, int pos)
{
	// TODO
	if (pos < 0 || pos >= heap->size) return;

	if (2 * pos + 1 < heap->size)
	{
		int maxChild = 2 * pos + 1;
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

void reheapDown_Iter(HEAP* heap, int pos)
{
	if (pos < 0 || pos >= heap->size) return;

	int curData = heap->data[pos];
	
	while (2 * pos + 1 < heap->size)
	{
		int maxChild = 2 * pos + 1;
		if (maxChild + 1 < heap->size && heap->data[maxChild] < heap->data[maxChild + 1])
			maxChild++;

		if (curData < heap->data[maxChild])
		{
			heap->data[pos] = heap->data[maxChild];
			pos = maxChild;
		}
		else
			break;
	}
	heap->data[pos] = curData;
}
