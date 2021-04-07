#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "heapADT.h"

int main()
{
	HEAP* heap = heapCreate();
	int size;
	printf("Input data size (under 100) : "); //�Է��� ���� ����
	scanf("%d", &size);

	int* data = (int*)malloc(sizeof(int) * size);
	printf("Input data : "); //���� �Է�
	for (int i = 0; i < size; i++)
		scanf("%d", &data[i]);

	for (int i = 0; i < size; i++) //���� ����. (Reheapup�� size��ŭ �ݺ��ؼ� �ص� �� ���� ���������� ����1ó�� �õ���.)
	{
		if(!heapInsert(heap, data[i]))
			printf("Error: inserting %d\n", data[i]);
	}
	printf("heap data : ");
	heapTraverse(heap); //�� ���
	
	size = heap->size; //�� insert�� ������ ��츦 ����� size ����
	int* sorted = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++)
		sorted[i] = heapDelete(heap); //ū ������� sorted�迭�� ����
	
	printf("Sort descending : ");
	for (int i = 0; i < size; i++) //��������
		printf("%d ", sorted[i]);
	printf("\nSort ascending : "); 
	for (int i = size-1; i>=0; i--) //��������
		printf("%d ", sorted[i]);
}