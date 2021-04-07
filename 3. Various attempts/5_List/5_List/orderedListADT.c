#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

LIST* createList(int(*compare)(STUDENT* pArg1, STUDENT* pArg2))
{
	// TODO
	LIST* list = (LIST*)malloc(sizeof(LIST));
	if (list == NULL) return NULL;
	list->pos = NULL;
	list->head = NULL;
	list->rear = NULL;
	list->compare = compare;
	list->listSize = 0;
	return list;
}

void destoryList(LIST* pList)
{
	// TODO
	if (pList)
	{
		NODE* del;
		while (!isEmpty(pList))
		{
			free(pList->head->pData);
			del = pList->head;
			pList->head = pList->head->next;
			free(del);
			pList->listSize--;
		}
		free(pList);
	}
}

bool insertData(LIST* pList, studentId id, char* name, char* email)
{
	// TODO
	NODE* pPre = NULL;
	NODE* pCur = NULL;
	if (!_doSearch(pList, &pPre, &pCur, id))
	{
		STUDENT* student;
		if (makeStudent(&student, id, name, email))
		{
			if (_doInsert(pList, pPre, student))
				return true;
		}
	}
	return false;
}

bool removeData(LIST* pList, studentId pKey)
{
	// TODO
	NODE* pPre = NULL;
	NODE* pCur = NULL;
	if (_doSearch(pList, &pPre, &pCur, pKey))
	{
		_doRemove(pList, pPre, pCur);
		return true;
	}
	return false;
}

bool searchData(LIST* pList, studentId pKey, STUDENT** pDataOut)
{
	// TODO
	NODE* pPre = NULL;
	NODE* pCur = NULL;

	if (_doSearch(pList, &pPre, &pCur, pKey))
	{
		(*pDataOut) = pCur->pData;
		return true;
	}
	return false;
}

int listSize(LIST* pList)
{
	// TODO
	return pList->listSize;
}

bool isEmpty(LIST* pList)
{
	// TODO
	if (pList->listSize <= 0) return true;
	return false;
}

void initIterator(LIST* pList)
{
	pList->pos = NULL;
}

bool iterateList(LIST* pList, STUDENT** pDataOut)
{
	// TODO
	if (pList->pos == NULL)
	{
		pList->pos = pList->head;
	}
	else
	{
		pList->pos = pList->pos->next;
	}

	if (pList->pos == NULL)
		return false;

	*pDataOut = pList->pos->pData;
	return true;
}

void printList(LIST* pList, void(*print)(STUDENT* pArg))
{
	// TODO
	NODE* temp = pList->head;
	for (int i = 0; i < listSize(pList); i++)
	{
		print(temp->pData);
		temp = temp->next;
	}
}

static bool _doInsert(LIST* pList, NODE* pPre, STUDENT* pDataIn)
{
	// TODO
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	if (newnode == NULL) return false;

	newnode->pData = pDataIn;
	newnode->next = NULL;

	if (pPre == NULL)
	{
		newnode->next = pList->head;
		pList->head = newnode;
		if (pList->listSize <= 0)
			pList->rear = newnode;
	}
	else
	{
		newnode->next = pPre->next;
		pPre->next = newnode;
		if (newnode->next == NULL)
			pList->rear = newnode;
	}
	pList->listSize++;
	return true;
}

static void _doRemove(LIST* pList, NODE* pPre, NODE* pCur)
{
	// TODO
	if (pPre == NULL)
	{
		pList->head = pCur->next;
	}
	else
	{
		pPre->next = pCur->next;
	}

	if (pCur->next == NULL)
		pList->rear = pCur;

	pList->listSize--;
	free(pCur->pData);
	free(pCur);
}

static bool _doSearch(LIST* pList, NODE** pPre, NODE** pLoc, studentId pKey)
{
	// TODO
	for (*pPre = NULL, *pLoc = pList->head; *pLoc != NULL; *pPre = *pLoc, *pLoc = (*pLoc)->next)
	{
		if (pList->compare((*pLoc)->pData, (STUDENT*)pKey) == 0) // 데이터 찾음
			return true;
		else if (pList->compare((*pLoc)->pData, (STUDENT*)pKey) > 0) // 현재 값이 찾으려는 데이터보다 큼
			break;
	}
	return false;
}

bool makeStudent(STUDENT** pDataOut, studentId id, char* name, char* email)
{
	// TODO
	*pDataOut = (STUDENT*)malloc(sizeof(STUDENT));
	(*pDataOut)->id = id;
	(*pDataOut)->name = name;
	(*pDataOut)->email = email;
	return true;
}

void printStudent(STUDENT* pStudent)
{
	// TODO
	printf("STUDENT ID: %d\n", pStudent->id);
	printf("NAME: %s\n", (char*)(pStudent->name));
	printf("EMAIL: %s\n", (char*)(pStudent->email));
	printf("--------------------\n");
}

int cmpStudentId(STUDENT* pStudent1, STUDENT* pStudent2)
{
	// TODO
	return pStudent1->id - (studentId)pStudent2;
}
