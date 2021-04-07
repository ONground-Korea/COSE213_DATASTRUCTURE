#pragma once
#include "bstADT.h"

BST_TREE* bstCreate()
{
	BST_TREE* pTree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if (pTree)
	{
		pTree->root = NULL;
		pTree->count = 0;
	}

	return pTree;
}

void bstDestroy(BST_TREE* pTree)
{
	if (pTree)
	{
		_bstDestroy(pTree->root);
		pTree->count = 0;

		free(pTree);
	}
}

void _bstDestroy(TREE_NODE* root)
{
	if (root)
	{
		_bstDestroy(root->left);
		_bstDestroy(root->right);
		free(root);
	}
}

bool itemInsert(BST_TREE* pTree, STUDENT_GRADE data)
{
	// TODO
	TREE_NODE* newnode = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	if (newnode == NULL) return NULL;

	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	if (pTree->count == 0)
		pTree->root = newnode;
	else
		_bstInsert(pTree, pTree->root, newnode);

	pTree->count++;
	return true;
}
TREE_NODE* _bstInsert(BST_TREE* tree, TREE_NODE* root, TREE_NODE* newPtr)
{
	// TODO
	if (root == NULL) return newPtr;

	if (root->data.score > newPtr->data.score)
		root->left = _bstInsert(tree, root->left, newPtr);
	else if(root->data.score<=newPtr->data.score)
		root->right = _bstInsert(tree, root->right, newPtr);

	return root;
}
bool itemDelete(BST_TREE* pTree, int key)
{
	// TODO
	int flag = 0;
	int flag2 = 0;
	while (pTree->count > 0)
	{
		TREE_NODE* del = _bstSearch(pTree->root, key);
		if (del)
		{
			_bstDelete(pTree->root, key);
			pTree->count--;
			flag = 1;
		}
		else flag2 = 1;
		if (flag2 == 1) break;
	}
	if (flag == 1) return true;
	else return false;
}
TREE_NODE* _bstDelete(TREE_NODE* root, int key)
{
	// TODO
	if (root == NULL) return root;

	if (key < root->data.score)
		root->left = _bstDelete(root->left, key);
	else if (key > root->data.score)
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
			root->left = _bstDelete(root->left, del->data.score);
		}
	}
	return root;
}
TREE_NODE* itemSearch(BST_TREE* pTree, int key)
{
	// TODO
	if (pTree->count > 0)
		return _bstSearch(pTree->root, key);
	else
		return NULL;
}
TREE_NODE* _bstSearch(TREE_NODE* root, int key)
{
	// TODO
	if (root)
	{
		if (key < root->data.score)
			return _bstSearch(root->left, key);
		else if (key > root->data.score)
			return _bstSearch(root->right, key);
		else
			return root;
	}
	else
		return NULL;
}
void bstTraverse(BST_TREE* pTree, void(*process)(TREE_NODE* root))
{
	printf("----------\n");
	printf("Node nums: %d\n", pTree->count);
	_bstTraverse(pTree->root, process);
}

void _bstTraverse(TREE_NODE* root, void(*process)(TREE_NODE* root))
{
	if (root)
	{
		_bstTraverse(root->left, process);
		process(root);
		_bstTraverse(root->right, process);
	}
}

void bstPrintData(TREE_NODE* root)
{
	if (root)
	{
		printf("%s(%d)'s score: %d\n", root->data.name, root->data.id, root->data.score);
	}
}

bool bstEmpty(BST_TREE* pTree)
{
	return pTree->count == 0;
}

int bstCount(BST_TREE* pTree)
{
	return pTree->count;
}