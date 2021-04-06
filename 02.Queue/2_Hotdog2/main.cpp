#define _CRT_SECURE_NO_WARNINGS
#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>

int hotdogsSold(int numCustomers, int* patience)
{
	// TODO
	QUEUE* queue1 = createQueue();
	int hotdogcnt = 0, time = 0;
	int* pat;
	int PATIENCE;
	int flag = 0;
	for (int i = 0; i < numCustomers; i++)
	{
		pat = (int*)malloc(sizeof(int));
		*pat = patience[i];
		enqueue(queue1, pat);
	}
	
	while (queueCount(queue1) > 0)
	{
		PATIENCE = *(int*)queueFront(queue1);
		if (PATIENCE >= time)
		{
			hotdogcnt++;
			if (flag == 1)
			{
				flag = 0;
				time++;
			}
			else flag++;
		}
		dequeue(queue1);
	}
	destroyQueue(queue1);
	return hotdogcnt;
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
	free(patience);
	return 0;
}