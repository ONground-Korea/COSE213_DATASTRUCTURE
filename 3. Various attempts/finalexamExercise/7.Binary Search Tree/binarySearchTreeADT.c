#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "binarySearchTreeADT.h"
#include <stdlib.h>

BST_TREE* bstCreate()
{
	// TODO
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if (tree == NULL) return NULL;

	tree->count = 0;
	tree->root = NULL;

	return tree;
}

void bstDestroy(BST_TREE* tree)
{
	// TODO
	if (tree)
	{
		_bstDestroy(tree->root);
		free(tree);
	}
}

void _bstDestroy(TREE_NODE* root)
{
	// TODO
	if (root == NULL) return;
	if (root->left) _bstDestroy(root->left);
	if (root->right) _bstDestroy(root->right);
	free(root);
}

bool bstInsert(BST_TREE* tree, int data)
{
	// TODO
	TREE_NODE* newnode = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	if (newnode == NULL) return false;

	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	if (tree->count == 0)
		tree->root = newnode;
	else
		_bstInsert(tree, tree->root, newnode);
	
	tree->count++;
	return true;
}

TREE_NODE* _bstInsert(BST_TREE* tree, TREE_NODE* root, TREE_NODE* newPtr)
{
	// TODO
	if (root == NULL) return newPtr;

	if (root->data > newPtr->data)
		root->left = _bstInsert(tree, root->left, newPtr);
	else
		root->right = _bstInsert(tree, root->right, newPtr);

	return root;
}

void bstDelete(BST_TREE* tree, int key)
{
	// TODO
	if (tree->count > 0)
	{
		TREE_NODE* del = _bstSearch(tree->root, key);
		if (del)
		{
			_bstDelete(tree->root, key);
			tree->count--;
		}
	}
}

TREE_NODE* _bstDelete(TREE_NODE* root, int key)
{
	// TODO
	if (root == NULL) return root;

	if (key < root->data)
		root->left = _bstDelete(root->left, key);
	else if (key > root->data)
		root->right = _bstDelete(root->right, key);
	else
	{
		TREE_NODE* del = NULL;
		if (!root->right)
		{
			del = root;
			root = root->left;
			free(del);
			return root;
		}
		else if (!root->left)
		{
			del = root;
			root = root->right;
			free(del);
			return root;
		}
		else
		{
			for (del = root->left; del->right != NULL; del = del->right);
			root->data = del->data;
			root->left = _bstDelete(root->left, del->data);
		}
	}
	return root;
}

TREE_NODE* bstSearch(BST_TREE* tree, int key)
{
	// TODO
	if (tree->count > 0)
		return _bstSearch(tree->root, key);
	else
		return NULL;
}

TREE_NODE* _bstSearch(TREE_NODE* root, int key)
{
	// TODO
	if (root)
	{
		if (key < root->data)
			return _bstSearch(root->left, key);
		else if (key > root->data)
			return _bstSearch(root->right, key);
		else
			return root;
	}
	else
		return NULL;
}

TREE_NODE* _bstSearchIter(TREE_NODE* root, int key)
{
	while (root != NULL)
	{
		if (key < root->data)
			root = root->left;
		else if (key > root->data)
			root = root->right;
		else
			break;
	}
	return root;
}

void bstTraverse(BST_TREE* tree, void(*process)(TREE_NODE* root))
{
	// TODO
	if (tree->root)
		_bstTraverse(tree->root, process);
	printf("\n");
}

void _bstTraverse(TREE_NODE* root, void(*process)(TREE_NODE* root))
{
	// TODO
	if (root)
	{
		_bstTraverse(root->left, process);
		(*process)(root);
		_bstTraverse(root->right, process);
	}
	return;
}

void bstPrintData(TREE_NODE* root)
{
	if (root)
	{
		printf("%d\t", root->data);
	}
}

bool bstEmpty(BST_TREE* tree)
{
	return tree->count == 0;
}

int bstCount(BST_TREE* tree)
{
	return tree->count;
}