#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queueADT.h"

QUEUE* createQueue(void)
{
	// TODO
	QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
	if (queue == NULL) return NULL;

	queue->count = 0;
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

void destroyQueue(QUEUE* queue)
{
	// TODO
	if (queue)
	{
		while (queueCount(queue) > 0)
			dequeue(queue);
		free(queue);
	}
}

void enqueue(QUEUE* queue, void* dataPtr)
{
	// TODO
	QUEUE_NODE* newnode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	if (newnode == NULL) return;

	newnode->dataPtr = dataPtr;
	newnode->next = NULL;

	if (queueCount(queue) == 0)
	{
		queue->front = newnode;
		queue->rear = newnode;
	}
	else
	{
		queue->rear->next = newnode;
		queue->rear = newnode;
	}
	queue->count++;
}

void dequeue(QUEUE* queue)
{
	// TODO
	if (queueCount(queue) <= 0) return;
	QUEUE_NODE* del = queue->front;
	queue->front = del->next;
	if (queue->front == NULL) queue->rear = NULL;
	queue->count--;
	free(del->dataPtr);
	free(del);
}

void* queueFront(QUEUE* queue)
{
	// TODO
	if (queueCount(queue) <= 0)
		return NULL;
	return queue->front->dataPtr;
}

int queueCount(QUEUE* queue)
{
	// TODO
	return queue->count;
}
