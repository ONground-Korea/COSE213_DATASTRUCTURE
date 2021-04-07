#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define HEAP_UNIT 100

typedef int studentId;

typedef struct
{
	studentId id;				// student ID 
	char name[20]; 				// student Name 
	int score;					// student's score 
} STUDENT_GRADE;

typedef struct
{
	STUDENT_GRADE* data;
	int size;
	int capacity;
} HEAP;

HEAP* heapCreate();
void heapDestroy(HEAP* pHeap);

bool studentInsert(HEAP* pHeap, STUDENT_GRADE val);
bool studentDelete(HEAP* pHeap);
void heapSort(STUDENT_GRADE* outArr, STUDENT_GRADE* sourceArr, int size);

int heapCount(HEAP* pHeap);
bool heapFull(HEAP* pHeap);
bool heapEmpty(HEAP* pHeap);
void heapTraverse(HEAP* pHeap);

void reheapUp(HEAP* heap, int pos);
void reheapDown(HEAP* heap, int pos);
