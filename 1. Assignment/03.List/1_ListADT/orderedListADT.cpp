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
	if (!_doSearch(pList, &pPre, &pCur, id)) // ����Ʈ�� ������ student id�� ������ insert������
	{
		STUDENT* student;
		if (makeStudent(&student, id, name, email))
		{
			if (_doInsert(pList, pPre, student)) // insert�� ���������� �Ǹ�
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

	if (_doSearch(pList, &pPre, &pCur, pKey)) // ����Ʈ�� �����Ϸ��� �ϴ� �����Ͱ� �����Ѵٸ�
	{
		_doRemove(pList, pPre, pCur); // ����
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

	if (pPre == NULL) // ���� ó�� ��忡 �߰��ϰų� ����Ʈ�� ��尡 �ϳ��� ���� ��.
	{
		newnode->next = pList->head;
		pList->head = newnode;
		if (pList->listSize <= 0) // ����Ʈ�� ��尡 �ϳ��� ���� ��.(newnode �ϳ��� ä��������, ���� listSize++����)
		{
			pList->rear = newnode;
		}
	}
	else // ����Ʈ�� �߰��̳� ���� ��带 �߰��� ���
	{
		newnode->next = pPre->next;
		pPre->next = newnode;
		if (newnode->next == NULL) // newnode�� �� �ڿ� ������ rear�� newnode�� ����.
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
	if (pPre == NULL) // ���� ù��° ��� ����
	{
		pList->head = pCur->next;
	}
	else // ù��° �̿� �ٸ� ��� ����
	{
		pPre->next = pCur->next;
	}

	if (pCur->next == NULL) //pCur�� ������ ����� ��
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
		if (pList->compare((*pLoc)->pData, (STUDENT*)pKey) == 0) // ������ ã��
			return true;
		else if (pList->compare((*pLoc)->pData, (STUDENT*)pKey) > 0) // ���� ���� ã������ �����ͺ��� ŭ
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
