#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STR_MAX 32

//typedef int studentId;

typedef struct
{
	int id;
	void* name;
	void* email;
} STUDENT;

typedef struct node
{
	STUDENT* pData;
	struct node* next;
} NODE;

typedef struct
{
	int listSize;
	NODE* pos;
	NODE* head;
	NODE* rear;
	int(*compare) (STUDENT* pArg1, STUDENT* pArg2);
} LIST;

LIST* createList(int(*compare)(STUDENT* pArg1, STUDENT* pArg2));
void destoryList(LIST* pList);
bool insertData(LIST* pList, int id, void* name, void* email);
bool removeData(LIST* pList, int pKey);
bool searchData(LIST* pList, int pKey, STUDENT** pDataOut);
int listSize(LIST* pList);
bool isEmpty(LIST* pList);
void initIterator(LIST* pList);
bool iterateList(LIST* pList, STUDENT** pDataOut);
void printList(LIST* pList, void(*print)(STUDENT* pArg));

static bool _doInsert(LIST* pList, NODE* pPre, STUDENT* pDataIn);
static void _doRemove(LIST* pList, NODE* pPre, NODE* pCur);
static bool _doSearch(LIST* pList, NODE** pPre, NODE** pCur, int pKey);

bool makeStudent(STUDENT** pDataOut, int id, void* name, void* email);
void printStudent(STUDENT* pArg);
int cmpStudentId(STUDENT* student1, STUDENT* student2);
NODE* doreverse(LIST* pList);
void* reverse(LIST* pList);

