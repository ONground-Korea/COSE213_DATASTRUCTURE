#include <stdio.h>
#include "heapADT.h"

void printHeader(const char* title);
void testInsertion(HEAP* pHeap);
void testDeletion(HEAP* pHeap);
void testHeapSort();

STUDENT_GRADE dummyData[] = {
	{ 2020,	"Park",		70 },
	{ 2019,	"Choi",		70 },
	{ 2018,	"Oh",		80 },
	{ 2017,	"Hahn",		60 },
	{ 2016,	"Son",		95 },
	{ 2015,	"Jo",		60 },
	{ 2014,	"Kim",		75 },
	{ 2013,	"Chung",	100 },
	{ 2012,	"Ahn",		70 },
	{ 2011,	"Jang",		85 },
	{ 2010,	"Lee",		50 },
};

int expect[] = { 50, 60, 60, 70, 70, 70, 75, 80, 85, 95, 100 };

int main()
{
	HEAP* heap = heapCreate();

	printHeader("Insertion Test");
	testInsertion(heap);

	printHeader("Deletion Test");
	testDeletion(heap);

	heapDestroy(heap);

	//////////////////////////////
	printHeader("HeapSort Test");
	testHeapSort();

	return 0;
}

void testInsertion(HEAP* pHeap)
{
	for (int i = 0; i < sizeof(dummyData) / sizeof(STUDENT_GRADE); i++)
	{
		if (studentInsert(pHeap, dummyData[i]) && pHeap->size == i + 1)
		{
			printf("PASS\n");
		}
		else
		{
			printf("FAIL (score: %d)\n", dummyData[i].score);
		}
	}

	heapTraverse(pHeap);
}

void testDeletion(HEAP* pHeap)
{

	for (int i = 0; i < sizeof(dummyData) / sizeof(STUDENT_GRADE); i++)
	{
		if (pHeap->data[0].score == expect[i] && studentDelete(pHeap))
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR: (score: %d)\n", expect[i]);
		}
	}
}

void testHeapSort()
{
	STUDENT_GRADE result[sizeof(dummyData) / sizeof(STUDENT_GRADE)];
	heapSort(result, dummyData, sizeof(dummyData) / sizeof(STUDENT_GRADE));

	for (int i = 0; i < sizeof(dummyData) / sizeof(STUDENT_GRADE); i++)
	{
		if (result[i].score == expect[i])
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR: (expect: %d / real: %d)\n", expect[i], result[i].score);
		}
	}
}

void printHeader(const char* title)
{
	printf("\n####################\n# %s\n", title);
}
