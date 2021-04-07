#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "heapADT.h"

HEAP* heapCreate()
{
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));

	if (!heap) return NULL;

	heap->size = 0;
	heap->capacity = HEAP_UNIT;
	heap->data = (STUDENT_GRADE*)malloc(HEAP_UNIT * sizeof(STUDENT_GRADE));

	return heap;
}

void heapDestroy(HEAP* pHeap)
{
	free(pHeap->data);
	free(pHeap);
}

bool studentInsert(HEAP* pHeap, STUDENT_GRADE val)
{
	// TODO
	if (heapFull(pHeap)) return false;

	pHeap->data[pHeap->size++] = val;
	reheapUp(pHeap, pHeap->size - 1);
	return true;
}
void reheapUp(HEAP* heap, int pos)
{
	// TODO
	if (pos <= 0 || pos >= heap->size) return;

	int parentIdx = (pos - 1) / 2;
	if (heap->data[parentIdx].score > heap->data[pos].score)
	{
		STUDENT_GRADE temp = heap->data[pos];
		heap->data[pos] = heap->data[parentIdx];
		heap->data[parentIdx] = temp;
		reheapUp(heap, parentIdx);
	}
}
bool studentDelete(HEAP* pHeap)
{
	// TODO
	if (heapEmpty(pHeap)) return false;

	pHeap->data[0] = pHeap->data[--pHeap->size];
	reheapDown(pHeap, 0);
	return true;
}
void reheapDown(HEAP* heap, int pos)
{
	// TODO
	if (pos < 0 || pos >= heap->size) return;

	if (2 * pos + 1 < heap->size)
	{
		int maxChild = 2 * pos + 1;
		if (maxChild + 1 < heap->size && heap->data[maxChild].score > heap->data[maxChild + 1].score)
			maxChild++;

		if (heap->data[pos].score > heap->data[maxChild].score)
		{
			STUDENT_GRADE temp = heap->data[pos];
			heap->data[pos] = heap->data[maxChild];
			heap->data[maxChild] = temp;
			reheapDown(heap, maxChild);
		}
	}
}
void heapSort(STUDENT_GRADE* outArr, STUDENT_GRADE* sourceArr, int size)
{
	// TODO
	HEAP* heap = heapCreate();

	for (int i = 0; i < size; i++)
		studentInsert(heap, sourceArr[i]);

	for (int i = 0; i < size; i++)
	{
		outArr[i] = heap->data[0];
		studentDelete(heap);
	}
	heapDestroy(heap);
}

int heapCount(HEAP* pHeap)
{
	return pHeap->size;
}

bool heapFull(HEAP* pHeap)
{
	return pHeap->size >= pHeap->capacity;
}

bool heapEmpty(HEAP* pHeap)
{
	return pHeap->size == 0;
}

void heapTraverse(HEAP* pHeap)
{
	printf("----------\n");
	printf("Num items: %d\n", pHeap->size);
	for (int i = 0; i < pHeap->size; i++)
	{
		printf("%s(%d)'s score: %d\n", pHeap->data[i].name, pHeap->data[i].id, pHeap->data[i].score);
	}
	printf("\n");
}

