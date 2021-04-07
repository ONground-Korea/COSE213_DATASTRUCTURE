#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queueADT.h"

QUEUE* createQueue(void)
{
	// TODO
	QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
	if (queue == NULL)return NULL;

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
		QUEUE_NODE* del;
		while (queue->count > 0)
		{
			free(queue->front->dataPtr);
			del = queue->front;
			queue->front = queue->front->next;
			free(del);
			queue->count--;
		}
		free(queue);
	}
}

void enqueue(QUEUE* queue, void* dataPtr)
{
	// TODO
	QUEUE_NODE* newnode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	if (newnode == NULL)return NULL;

	newnode->dataPtr = dataPtr;
	newnode->next = NULL;

	if (queue->count == 0)
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
	if (queue->count <= 0)
		return;
	QUEUE_NODE* del = queue->front;
	queue->front = queue->front->next;
	if (queue->front == NULL)
		queue->rear = NULL;
	queue->count--;
	free(del->dataPtr);
	free(del);
}

void* queueFront(QUEUE* queue)
{
	// TODO
	if (queue->count <= 0) return NULL;
	return queue->front->dataPtr;
}

int queueCount(QUEUE* queue)
{
	// TODO
	return queue->count;
}
