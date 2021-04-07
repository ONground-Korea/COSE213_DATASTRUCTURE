#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

LIST* createList(int(*fpCompare)(double avgLStudent, double avgRStudent),
	void(*fpPrint)(STUDENT_GRADE* pArg))
{
	LIST* list;

	list = (LIST*)malloc(sizeof(LIST));
	if (list)
	{
		list->head = NULL;
		list->pos = NULL;
		list->rear = NULL;
		list->listCount = 0;
		list->fpCompare = fpCompare;
		list->fpPrint = fpPrint;
	}

	return list;
}

void destoryList(LIST* pList)
{
	// TODO
	if (pList)
	{
		LIST_NODE* del;
		while (pList->listCount > 0)
		{
			free(pList->head->pData);
			del = pList->head;
			pList->head = pList->head->next;
			free(del);
			pList->listCount--;
		}
		free(pList);
	}
}

bool insertData(LIST* pList,
	studentId id, double gradeDS, double gradeDB, double gradeOS)
{
	LIST_NODE* pPre = NULL;
	LIST_NODE* pCur = NULL;

	STUDENT_GRADE* pData;
	makeStudentGrade(&pData, id, gradeDS, gradeDB, gradeOS);
	_exeFind(pList, &pPre, &pCur, pData->avg);

	initTraversePos(pList);
	return _exeInsert(pList, pPre, pData);
}

static bool _exeInsert(LIST* pList, LIST_NODE* pPre, STUDENT_GRADE* pDataIn)
{
	// TODO
	LIST_NODE* newnode = (LIST_NODE*)malloc(sizeof(LIST_NODE));
	if (newnode == NULL)return false;

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
	pList->listCount++;
	initTraversePos(pList);
	return true;
}

bool deleteData(LIST* pList, double avg)
{
	// TODO
	LIST_NODE* pPre = NULL;
	LIST_NODE* pCur = NULL;
	if (_exeFind(pList, &pPre, &pCur, avg))
	{
		_exeDelete(pList, pPre, pCur);
		return true;
	}
	return false;
}

static void _exeDelete(LIST* pList, LIST_NODE* pPre, LIST_NODE* pCur)
{
	// TODO
	LIST_NODE* del = pCur;
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
	pList->listCount--;
	free(del->pData);
	free(del);
	initTraversePos(pList);
}

bool findData(LIST* pList, double avg, STUDENT_GRADE** pDataOut)
{
	// TODO
	LIST_NODE* pPre = NULL;
	LIST_NODE* pCur = NULL;
	if (_exeFind(pList, &pPre, &pCur, avg))
	{
		*pDataOut = pCur->pData;
		return true;
	}
	return false;
}

static bool _exeFind(LIST* pList, LIST_NODE** pPre, LIST_NODE** pCur, double avg)
{
	// TODO
	for (*pPre = NULL, *pCur = pList->head; *pCur != NULL; *pPre = *pCur, *pCur = (*pCur)->next)
	{
		if (cmpStudentGrade((*pCur)->pData->avg, (*pCur)->pData->avg) == 0)
			return true;
		if (cmpStudentGrade((*pCur)->pData->avg, (*pCur)->pData->avg) < 0)
			break;
	}
	return false;
}

int listCount(LIST* pList)
{
	return pList->listCount;
}

void initTraversePos(LIST* pList)
{
	pList->pos = NULL;
}

bool traverseList(LIST* pList, STUDENT_GRADE** pDataOut)
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

int cmpStudentGrade(double avgLStudent, double avgRStudent)
{
	// TODO
	if (avgLStudent > avgRStudent)
		return 1;
	if (avgLStudent < avgRStudent)
		return -1;
	else
		return 0;
}

bool makeStudentGrade(STUDENT_GRADE** pDataOut,
	studentId id, double gradeDS, double gradeDB, double gradeOS)
{
	STUDENT_GRADE* obj = (STUDENT_GRADE*)malloc(sizeof(STUDENT_GRADE));
	if (obj == NULL)
		return false;

	obj->id = id;
	obj->gradeDS = gradeDS;
	obj->gradeDB = gradeDB;
	obj->gradeOS = gradeOS;
	obj->avg = (gradeDS + gradeDB + gradeOS) / NUM_SUBJECTS;

	*pDataOut = obj;

	return true;
}

void printList(LIST* pList)
{
	STUDENT_GRADE* pData;
	initTraversePos(pList);

	while (traverseList(pList, &pData))
	{
		pList->fpPrint(pData);
	}
	printf("====================\n");
}

void printStudentGrade(STUDENT_GRADE* pStudent)
{
	if (pStudent != NULL)
	{
		printf("STUDENT ID: %d\nData Structure: %.1f\nDatabases: %.1f\nOperating Systems: %.1f\nAvg: %.2f\n",
			pStudent->id,
			pStudent->gradeDS, pStudent->gradeDB, pStudent->gradeOS,
			pStudent->avg);
		printf("--------------------\n");
	}
}

