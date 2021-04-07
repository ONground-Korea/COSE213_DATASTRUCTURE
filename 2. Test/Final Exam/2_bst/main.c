#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bstADT.h"

void printHeader(const char* title);
void testInsertion(BST_TREE* pTree);
void testDeletion(BST_TREE* pTree);
void testFind(BST_TREE* pTree);

STUDENT_GRADE dummyData[] = {
	{ 1000,	"Park",		70 },
	{ 1001,	"Choi",		70 },
	{ 1002,	"Oh",		80 },
	{ 1003,	"Hahn",		60 },
	{ 1004,	"Son",		95 },
	{ 1005,	"Jo",		60 },
	{ 1006,	"Kim",		75 },
	{ 1007,	"Chung",	100 },
	{ 1008,	"Ahn",		70 },
	{ 1009,	"Jang",		85 },
	{ 1010,	"Lee",		50 },
};

#define DATA_NUM_	(sizeof(dummyData) / sizeof(int))

int main()
{
	BST_TREE* bstTree = bstCreate();

	printHeader("Insertion Test");
	testInsertion(bstTree);

	printHeader("Find Test");
	testFind(bstTree);

	printHeader("Deletion Test");
	testDeletion(bstTree);

	bstDestroy(bstTree);

	return 0;
}

void testInsertion(BST_TREE* pTree)
{
	for (int i = 0; i < sizeof(dummyData) / sizeof(STUDENT_GRADE); i++)
	{
		if (!itemInsert(pTree, dummyData[i]))
		{
			printf("INSERT FAIL: (ID: %d, NAME: %s)\n", dummyData[i].id, dummyData[i].name);
		}

		if (pTree->count == i + 1)
		{
			printf("PASS\n");
		}
		else
		{
			printf("FAIL\n");
		}
	}

	bstTraverse(pTree, bstPrintData);
}

void testFind(BST_TREE* pTree)
{
	int retreiveKey[] = { 100, 60, 23 };
	bool expect[] = { true, true, false };
	int expectId[] = { 1007, 1003, -1 };

	for (int i = 0; i < sizeof(retreiveKey) / sizeof(int); i++)
	{
		TREE_NODE* node = itemSearch(pTree, retreiveKey[i]);
		if (node && expect[i] && node->data.id == expectId[i])
		{
			printf("PASS\n");
		}
		else if (!node && !expect[i])
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR: %d", retreiveKey[i]);
			if (node)
			{
				printf("(Expect ID: %d / Real: %d, %s, %d)", expectId[i], node->data.id, node->data.name, node->data.score);
			}
			printf("\n");
		}
	}
}

void testDeletion(BST_TREE* pTree)
{
	int delKey[] = { 70, 95, 55, 60 };
	bool expect[] = { true, true, false, true };
	int expectNodeNum[] = { 8, 7, 7, 5 };

	for (int i = 0; i < sizeof(delKey) / sizeof(int); i++)
	{
		if (itemDelete(pTree, delKey[i]) == expect[i] && pTree->count == expectNodeNum[i])
		{
			bstTraverse(pTree, bstPrintData);
		}
		else
		{
			printf("ERROR: (Score: %d)\n", delKey[i]);
		}
	}
}

void printHeader(const char* title)
{
	printf("\n####################\n# %s\n", title);
}
