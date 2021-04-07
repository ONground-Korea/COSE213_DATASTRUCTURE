#include <stdio.h>
#include "heapADT.h"

int main()
{
	HEAP* heap = heapCreate();
	int val[] = { 100, 55, 234, 452, 10 };

	for (int i = 0; i < sizeof(val) / sizeof(int); i++)
	{
		if (!heapInsert(heap, val[i]))
		{
			printf("Error: inserting %d\n", val[i]);
		}

		heapTraverse(heap);
	}

	heapSort(val, sizeof(val) / sizeof(int));
	printf("Heap sort :: ");
	for (int i = 0; i < sizeof(val) / sizeof(int); i++)
		printf("%d ", val[i]);
	printf("\n");

	for (int i = 0; i < sizeof(val) / sizeof(int); i++)
	{
		heapDelete(heap);
		heapTraverse(heap);
	}

	heapDestroy(heap);

	return 0;

}