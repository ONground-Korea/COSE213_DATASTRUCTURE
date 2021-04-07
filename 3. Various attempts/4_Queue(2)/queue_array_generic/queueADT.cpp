#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>


QUEUE* createQueue(int size)
{
	QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
	if (queue == NULL) return NULL;

	queue->count = 0;
	queue->front = 0;
	queue->rear = -1;
	queue->size = size;
	queue->nodes = (void**)malloc(sizeof(void*) * size);
	if (queue->nodes == NULL) return NULL;

	return queue;
}
void destroyQueue(QUEUE* queue)
{
	if (queue)
	{
		free(queue->nodes);
		free(queue); 
	}
}
bool enqueue(QUEUE* queue, void* dataPtr)
{
	if (isFull(queue))
		return false;
	queue->rear = (queue->rear + 1) % (queue->size);
	queue->nodes[queue->rear] = dataPtr;
	queue->count++;
}
bool dequeue(QUEUE* queue)
{
	if (isEmpty(queue))
		return false;
	queue->front = (queue->front + 1) % (queue->size);
	queue->count--;
	return true;
}
bool queueFront(QUEUE* queue, void** dataPtr)
{
	if (isEmpty(queue))
		return false;
	*dataPtr = queue->nodes[queue->front];
	return true;
}
bool queueRear(QUEUE* queue, void** dataPtr)
{
	if (isEmpty(queue))
		return false;
	*dataPtr = queue->nodes[queue->rear];
	return true;
}
int queueCount(QUEUE* queue)
{
	return queue->count;
}
bool isFull(QUEUE* queue)
{
	if (queue->count >= queue->size)
		return true;
	else
		return false;
}
bool isEmpty(QUEUE* queue)
{
	if (queue->count <= 0)
		return true;
	else
		return false;
}