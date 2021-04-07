#pragma once
#include <stdbool.h>
#define STR_MAX 16

typedef struct node
{
	void* data;
	struct node* left;
	struct node* right;
} NODE;

NODE* createTree(NODE* left, const void* dataPtr, NODE* right);
void destroyTree(NODE* node);
void* treeData(NODE* node);
bool hasChild(NODE* node);
double evaluate(NODE* node);
