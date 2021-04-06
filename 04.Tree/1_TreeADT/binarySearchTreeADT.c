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
	if (root == NULL)
		return;
	if (root->left)
		_bstDestroy(root->left);
	if (root->right)
		_bstDestroy(root->right);
	free(root);
}

bool bstInsert(BST_TREE* tree, int data)
{
	// TODO
	TREE_NODE* newPtr = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	if (newPtr == NULL) return false;

	newPtr->data = data;
	newPtr->left = NULL;
	newPtr->right = NULL;

	if (tree->count == 0) //tree가 비어있으면 newPtr이 root노드가 됨.
		tree->root = newPtr;
	else
		_bstInsert(tree, tree->root, newPtr);
	
	tree->count++;
	return true;
}

TREE_NODE* _bstInsert(BST_TREE* tree, TREE_NODE* root, TREE_NODE* newPtr)
{
	// TODO
	if (root == NULL) return newPtr;

	if (newPtr->data < root->data)
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
		TREE_NODE* del = bstSearch(tree, key);
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
	if (root == NULL)
		return root;

	if (key < root->data)
		root->left = _bstDelete(root->left, key);
	else if (key > root->data)
		root->right = _bstDelete(root->right, key);
	else // 현재 노드가 삭제하려는 노드일 경우
	{
		TREE_NODE* del = NULL;
		if (!root->right) // 오른쪽 노드가 없을 때(자식이 없거나 l_sub만 있을 때)
		{
			del = root;
			root = root->left;
			free(del);
			return root;
		}
		else if (!root->left) // 왼쪽 노드가 없을 때(r_sub만 있을 때)
		{
			del = root;
			root = root->right;
			free(del);
			return root;
		}
		else // 왼쪽 오른쪽 자식이 다 있을 때 -> l_sub에서 가장 큰 노드를 루트노드로 사용한다.
		{
			for (del = root->left; del->right != NULL; del = del->right); // del을 l_sub의 가장 큰 노드로 옮김.
			root->data = del->data; // 루트노드의 데이터에 del노드의 데이터를 넣음.
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
		else //데이터를 찾았을 때
			return root;
	}
	else
		return NULL;
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