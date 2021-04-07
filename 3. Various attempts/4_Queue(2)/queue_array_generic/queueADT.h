#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QUEUE {
	void** nodes;
	int front;
	int rear;
	int count;
	int size;
}QUEUE;

QUEUE* createQueue(int size);
void destroyQueue(QUEUE* queue);
bool enqueue(QUEUE* queue, void* dataPtr);
bool dequeue(QUEUE* queue);
bool queueFront(QUEUE* queue, void** dataPtr);
bool queueRear(QUEUE* queue, void** dataPtr);
int queueCount(QUEUE* queue);
bool isFull(QUEUE* queue);
bool isEmpty(QUEUE* queue);