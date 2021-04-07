#define _CRT_SECURE_NO_WARNINGS
#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
int hotdogsSold(int numCustomers, int* patience)
{
	// TODO
	QUEUE* queue = createQueue(SIZE);
	int time = 0;
	int flag = 0;
	int hotdogs = 0;
	int* pat;

	for (int i = 0; i < numCustomers; i++)
	{
		pat = (int*)malloc(sizeof(int));
		*pat = patience[i];
		enqueue(queue, (void*)pat);
	}

	while (queueCount(queue) > 0)
	{
		void* front;
		if (queueFront(queue, &front))
		{
			if (*(int*)front >= time)
			{
				hotdogs++;
				if (flag == 1)
				{
					time++;
					flag -= 2;
				}
				flag++;
			}
			dequeue(queue);
		}
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