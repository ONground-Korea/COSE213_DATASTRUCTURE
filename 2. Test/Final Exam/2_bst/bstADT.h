#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int studentId;

typedef struct
{
	studentId id;				// student ID 
	char name[20]; 				// student Name 
	int score;					// student's score 
} STUDENT_GRADE;

typedef struct tree_node
{
	STUDENT_GRADE data;
	struct tree_node* left;
	struct tree_node* right;
} TREE_NODE;

typedef struct
{
	int count;
	TREE_NODE* root;
} BST_TREE;

BST_TREE* bstCreate();
void bstDestroy(BST_TREE* pTree);
static void _bstDestroy(TREE_NODE* root);

bool itemInsert(BST_TREE* pTree, STUDENT_GRADE data);
TREE_NODE* _bstInsert(BST_TREE* tree, TREE_NODE* root, TREE_NODE* newPtr);

bool itemDelete(BST_TREE* pTree, int key);
TREE_NODE* _bstDelete(TREE_NODE* root, int key);

TREE_NODE* itemSearch(BST_TREE* pTree, int key);
TREE_NODE* _bstSearch(TREE_NODE* root, int key);

void bstTraverse(BST_TREE* pTree, void(*process)(TREE_NODE* root));
void _bstTraverse(TREE_NODE* root, void (*process)(TREE_NODE* root));
void bstPrintData(TREE_NODE* root);

bool bstEmpty(BST_TREE* pTree);
int bstCount(BST_TREE* pTree);