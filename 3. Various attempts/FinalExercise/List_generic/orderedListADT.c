#define _CRT_SECURE_NO_WARNINGS
#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

LIST* createList(int(*compare)(STUDENT* pArg1, STUDENT* pArg2))
{
	// TODO
	LIST* list = (LIST*)malloc(sizeof(LIST));
	if (list == NULL) return NULL;

	list->compare = compare;
	list->head = NULL;
	list->pos = NULL;
	list->rear = NULL;
	list->listSize = 0;

	return list;
}

void destoryList(LIST* pList)
{
	// TODO
	if (pList)
	{
		NODE* del;
		while (pList->listSize > 0)
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

bool insertData(LIST* pList, int id, void* name, void* email)
{
	// TODO
	NODE* pPre;
	NODE* pCur;
	if (!_doSearch(pList, &pPre, &pCur, id)) // 리스트에 데이터가 없으면 삽입
	{
		STUDENT* student;
		if (makeStudent(&student, id, name, email)) // 학생을 만들면
		{
			if (_doInsert(pList, pPre, student)) // 삽입을 하면
			{
				return true;
			}

		}
	}
	return false;
}

bool removeData(LIST* pList, int pKey)
{
	// TODO
	NODE* pPre;
	NODE* pCur;
	if (_doSearch(pList, &pPre, &pCur, pKey)) // 데이터를 찾으면
	{
		_doRemove(pList, pPre, pCur);
		return true;
	}
	return false;
}

bool searchData(LIST* pList, int pKey, STUDENT** pDataOut)
{
	// TODO
	NODE* pPre;
	NODE* pCur;
	if (_doSearch(pList, &pPre, &pCur, pKey)) 
	{
		*pDataOut = pCur->pData;
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
	if (pList->listSize <= 0)
		return true;
	else
		return false;
}

void initIterator(LIST* pList)
{
	pList->pos = NULL;
}

bool iterateList(LIST* pList, STUDENT** pDataOut)
{
	// TODO
	if (pList->pos == NULL) // pos가 없으면
	{
		pList->pos = pList->head;
	}
	else
	{
		pList->pos = pList->pos->next;
	}
	
	if (pList->pos != NULL)
	{
		*pDataOut = pList->pos->pData;
		return true;
	}
	else // 끝까지 다 이터레이트 되면
	{
		return false;
	}
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
	printf("====================\n");
}

static bool _doInsert(LIST* pList, NODE* pPre, STUDENT* pDataIn)
{
	// TODO
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	if (newnode == NULL) return false;
	
	newnode->pData = pDataIn;
	newnode->next = NULL;

	if (pPre == NULL) // 데이터가 하나도 없으면
	{
		newnode->next = pList->head;
		pList->head = newnode;
		pList->rear = newnode;
	}
	else
	{
		newnode->next = pPre->next;
		pPre->next = newnode;
		if (newnode->next == NULL) // 데이터가 마지막꺼면 rear값 변경.
			pList->rear = newnode;
	}
	pList->listSize++;
	return true;
}

static void _doRemove(LIST* pList, NODE* pPre, NODE* pCur)
{
	// TODO
	NODE* del = pCur;
	if (pPre == NULL) // 지우려는 데이터가 첫번째거면
	{
		pList->head = pCur->next;
	}
	else
	{
		pPre->next = pCur->next;
	}

	if (pCur->next == NULL) // 마지막 데이터면
	{
		pList->rear = pPre;
	}
	pList->listSize--;
	free(del->pData);
	free(del);
}

static bool _doSearch(LIST* pList, NODE** pPre, NODE** pLoc, int pKey)
{
	// TODO
	for (*pPre = NULL, *pLoc = pList->head; *pLoc != NULL; *pPre = *pLoc, *pLoc = (*pLoc)->next)
	{
		if (pList->compare((*pLoc)->pData, (STUDENT*)&pKey) == 0)
			return true;
		if (pList->compare((*pLoc)->pData, (STUDENT*)&pKey) > 0)
			break;
	}
	return false;
}

bool makeStudent(STUDENT** pDataOut, int id, void* name, void* email)
{
	// TODO
	STUDENT* temp = (STUDENT*)malloc(sizeof(STUDENT));
	if (temp == NULL) return false;

	temp->id = id;
	temp->name = name;
	temp->email = email;
	*pDataOut = temp;
	return true;
}

void printStudent(STUDENT* pStudent)
{
	// TODO
	printf("STUDENT ID: %d\n", pStudent->id);
	printf("NAME: %s\n", (char*)pStudent->name);
	printf("EMAIL: %s\n", (char*)pStudent->email);
	printf("--------------------\n");
}

int cmpStudentId(STUDENT* pStudent1, STUDENT* pStudent2)
{
	// TODO
	int id1, id2;
	id1 = pStudent1->id;
	id2 = pStudent2->id;
	return id1 - id2;
}

NODE* doreverse(LIST* pList)
{
	NODE* p;
	NODE* q;
	NODE* r;
	p = pList->head;
	q = NULL;
	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	return q;
}
void* reverse(LIST* pList)
{
	pList->head = doreverse(pList);
	NODE* pre = pList->head;
	while (pre->next != NULL)
	{
		pre = pre->next;
	}
	pList->rear = pre;
}