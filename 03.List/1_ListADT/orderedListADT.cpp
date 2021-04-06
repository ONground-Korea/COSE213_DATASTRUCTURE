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

	list->listSize = 0;
	list->head = NULL;
	list->rear = NULL;
	list->pos = NULL;
	list->compare = compare;
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
	if (!_doSearch(pList, &pPre, &pCur, id)) // 리스트에 동일한 student id가 없으면 insert가능함
	{
		STUDENT* student;
		if (makeStudent(&student, id, name, email))
		{
			if (_doInsert(pList, pPre, student)) // insert가 정상적으로 되면
				return true;
		}
		/*student->id = id;
		strcpy(student->name, name);
		strcpy(student->email, email);*/
	}
	return false;
}

bool removeData(LIST* pList, studentId pKey)
{
	// TODO
	if(isEmpty(pList)) return false;
	NODE* pPre = NULL;
	NODE* pCur = NULL;

	if (_doSearch(pList, &pPre, &pCur, pKey)) // 리스트에 삭제하려고 하는 데이터가 존재한다면
	{
		_doRemove(pList, pPre, pCur); // 삭제
		return true;
	}
	else return false;
}

bool searchData(LIST* pList, studentId pKey, STUDENT** pDataOut)
{
	// TODO
	NODE* pPre = NULL;
	NODE* pCur = NULL;
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
	if (pList->listSize <= 0) return true;
	else return false;
}

void initIterator(LIST* pList)
{
	pList->pos = NULL;
}

bool iterateList(LIST* pList, STUDENT** pDataOut)
{
	// TODO
	if (pList->pos == NULL)
		pList->pos = pList->head;
	else
		pList->pos = pList->pos->next;
	
	if (pList->pos != NULL)
	{
		*pDataOut = pList->pos->pData;
		return true;
	}
	else
	{
		//*pDataOut = NULL;
		return false;
	}
}

void printList(LIST* pList, void(*print)(STUDENT* pArg))
{
	// TODO
	NODE* temp = pList->head;
	for (int i = 0; i < listSize(pList); i++)
	{
		(*print)(temp->pData);
		temp = temp->next;
	}
	printf("====================\n");
}

static bool _doInsert(LIST* pList, NODE* pPre, STUDENT* pDataIn)
{
	// TODO
	NODE* newnode = NULL;
	if (!(newnode = (NODE*)malloc(sizeof(NODE))))
		return false;
	newnode->pData = pDataIn;
	newnode->next = NULL;

	if (pPre == NULL) // 가장 처음 노드에 추가하거나 리스트에 노드가 하나도 없을 때.
	{
		newnode->next = pList->head;
		pList->head = newnode;
		if (pList->listSize <= 0) // 리스트에 노드가 하나도 없을 때.(newnode 하나만 채워졌을때, 아직 listSize++안함)
		{
			pList->rear = newnode;
		}
	}
	else // 리스트의 중간이나 끝에 노드를 추가할 경우
	{
		newnode->next = pPre->next;
		pPre->next = newnode;
		if (newnode->next == NULL) // newnode가 맨 뒤에 들어갔을때 rear을 newnode로 갱신.
		{
			pList->rear = newnode;
		}
	}
	(pList->listSize)++;
	return true;
}

static void _doRemove(LIST* pList, NODE* pPre, NODE* pCur)
{
	// TODO
	if (pPre == NULL) // 가장 첫번째 노드 삭제
	{
		pList->head = pCur->next;
	}
	else // 첫번째 이외 다른 노드 삭제
	{
		pPre->next = pCur->next;
	}

	if (pCur->next == NULL) //pCur이 마지막 노드일 때
	{
		pList->rear = pPre;
	}
	pList->listSize--;
	free(pCur);
}

static bool _doSearch(LIST* pList, NODE** pPre, NODE** pLoc, studentId pKey)
{
	// TODO
	for (*pPre = NULL, *pLoc = pList->head; *pLoc!= NULL; *pPre = *pLoc, *pLoc = (*pLoc)->next)
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
	if (*pDataOut == NULL) return false;
	else
	{
		(*pDataOut)->id = id;
		strcpy((*pDataOut)->name, name);
		strcpy((*pDataOut)->email, email);
		return true;
	}
}

void printStudent(STUDENT* pStudent)
{
	// TODO
	printf("STUDENT ID: %d\n", pStudent->id);
	printf("NAME: %s\n", pStudent->name);
	printf("EMAIL: %s\n", pStudent->email);
	printf("--------------------\n");
}

int cmpStudentId(STUDENT* pStudent1, STUDENT* pStudent2)
{
	// TODO
	return pStudent1->id - (studentId)pStudent2;
}
