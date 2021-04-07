#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "expressionTreeADT.h"

NODE* createTree(NODE* left, const char* dataPtr, NODE* right)
{
	// TODO
	NODE* tree = (NODE*)malloc(sizeof(NODE));
	if (tree == NULL) return NULL;

	strcpy(tree->data, dataPtr);
	tree->left = left;
	tree->right = right;
	return tree;
}

void destroyTree(NODE* node)
{
	// TODO
	if (node == NULL) return;
	if (node->left) destroyTree(node->left);
	if (node->right) destroyTree(node->right);
	free(node);
}

char* treeData(NODE* node)
{
	// TODO
	return node->data;
}

bool hasChild(NODE* node)
{
	// TODO
	if (node->left->data!=NULL && node->right->data!=NULL)
		return true;
	else
		return false;
}

double evaluate(NODE* node)
{
	// TODO
	if (!node)
		return 0;
	if (!node->left && !node->right)
		return atof(node->data);

	double left_val = evaluate(node->left);
	double right_val = evaluate(node->right);

	if (!strcmp(node->data, "+"))
		return left_val + right_val;
	if (!strcmp(node->data, "-"))
		return left_val - right_val;
	if (!strcmp(node->data, "*"))
		return left_val * right_val;
	if (!strcmp(node->data, "/"))
		return left_val / right_val;
}

