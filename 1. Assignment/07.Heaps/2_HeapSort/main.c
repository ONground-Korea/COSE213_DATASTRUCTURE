#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "heapADT.h"

int main()
{
	HEAP* heap = heapCreate();
	int size;
	printf("Input data size (under 100) : "); //입력할 숫자 개수
	scanf("%d", &size);

	int* data = (int*)malloc(sizeof(int) * size);
	printf("Input data : "); //숫자 입력
	for (int i = 0; i < size; i++)
		scanf("%d", &data[i]);

	for (int i = 0; i < size; i++) //힙에 저장. (Reheapup을 size만큼 반복해서 해도 힙 생성 가능하지만 과제1처럼 시도함.)
	{
		if(!heapInsert(heap, data[i]))
			printf("Error: inserting %d\n", data[i]);
	}
	printf("heap data : ");
	heapTraverse(heap); //힙 출력
	
	size = heap->size; //힙 insert가 실패할 경우를 대비해 size 갱신
	int* sorted = (int*)malloc(sizeof(int) * size);

	for (int i = 0; i < size; i++)
		sorted[i] = heapDelete(heap); //큰 순서대로 sorted배열에 저장
	
	printf("Sort descending : ");
	for (int i = 0; i < size; i++) //내림차순
		printf("%d ", sorted[i]);
	printf("\nSort ascending : "); 
	for (int i = size-1; i>=0; i--) //오름차순
		printf("%d ", sorted[i]);
}