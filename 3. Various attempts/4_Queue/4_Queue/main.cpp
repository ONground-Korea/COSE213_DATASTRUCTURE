#define _CRT_SECURE_NO_WARNINGS
#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>

int hotdogsSold(int numCustomers, int* patience)
{
	// TODO
	QUEUE* queue = createQueue();
	int* pat;
	int time = 0;
	int hotdogs = 0;
	for (int i = 0; i < numCustomers; i++)
	{
		pat = (int*)malloc(sizeof(int));
		*pat = patience[i];
		enqueue(queue, pat);
	}
	while (queueCount(queue) > 0)
	{
		if (*(int*)queueFront(queue) >= time)
		{
			hotdogs++;
			time++;
		}
		dequeue(queue);
	}
	destroyQueue(queue);
	return hotdogs;
}

int main()
{
	int numCustomers;
	int* patience;

	printf("Number of customers : ");
	scanf("%d", &numCustomers);
	patience = (int*)malloc(sizeof(int) * numCustomers);

	for (int i = 0; i < numCustomers; ++i)
	{
		printf("Patience of customer %d (1~9): ", i + 1);
		scanf("%d", &patience[i]);
	}

	printf("I sold %d hotdogs\n", hotdogsSold(numCustomers, patience));

	return 0;
}