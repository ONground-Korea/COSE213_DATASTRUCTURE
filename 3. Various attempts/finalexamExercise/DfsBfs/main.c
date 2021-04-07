#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stackADT.h"
#include "queueADT.h"

#define NUM_NODES 8
#define INF 0x7FFF
#define MAX_VERTICIES 50

//출처: https://ksj14.tistory.com/entry/깊이-우선-탐색-Depth-First-Search [:: ADVANCE ::]

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICIES];
} GraphType;

void init(GraphType* g) // 그래프 초기화
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICIES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) // 정점 삽입 연산
{
	if (((g->n) + 1) > MAX_VERTICIES)
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int u, int v) // 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
{
	GraphNode* node;
	if (u >= g->n || v >= g->n)
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}

	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_adj_list(GraphType* g)
{
	for (int i = 0; i < g->n; i++)
	{
		GraphNode* n = g->adj_list[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (n != NULL)
		{
			printf("-> %d ", n->vertex);
			n = n->link;
		}
		printf("\n");
	}
}
void dfs(int(*w)[NUM_NODES], bool selected[], int cur)
{
	printf("%d ", cur);
	selected[cur] = true;

	for (int i = 0; i < NUM_NODES; i++)
	{
		if (w[cur][i] != 0 && w[cur][i] != INF && !selected[i])
		{
			int next = i;
			dfs(w, selected, next);
		}
	}
}

void dfsStack(int(*w)[NUM_NODES], bool selected[], int cur)
{
	STACK* stack = createStack();
	pushStack(stack, (int*)cur);

	while (stack->count > 0)
	{
		cur = (int)stackTop(stack);
		popStack(stack);

		if (!selected[cur])
		{
			selected[cur] = true;
			printf("%d ", cur+1);
			for (int i = NUM_NODES-1; i >=0; i--)
			{
				if (w[cur][i] != 0 && w[cur][i] != INF && !selected[i])
				{
					pushStack(stack, (int*)i);
				}
			}
		}

	}
}

void dfs_list(GraphType* g, bool selected[], int v)
{
	GraphNode* w;
	selected[v] = true;
	printf("%d", v);
	for (w = g->adj_list[v]; w; w = w->link)
	{
		if (!selected[w->vertex])
		{
			dfs_list(g, selected, w->vertex);
		}
	}
}
void bfs(int(*w)[NUM_NODES], bool selected[], int cur)
{
	QUEUE* queue = createQueue();

	selected[cur] = true;
	printf("%d ", cur);
	enqueue(queue, (int*)cur);

	while (queue->count > 0)
	{
		cur = (int*)queueFront(queue);
		dequeue(queue);
		for (int i = 0; i < NUM_NODES; i++)
		{
			if (w[cur][i] != 0 && w[cur][i] != INF && !selected[i])
			{
				printf("%d ", i);
				selected[i] = true;
				enqueue(queue, (int*)i);
			}
		}
	}
}
int main()
{
	/*int w[NUM_NODES][NUM_NODES] = {
		{0,1,1,1,0},
		{1,0,1,0,1},
		{1,1,0,0,0},
		{1,0,0,0,1},
		{0,1,0,1,0},
	};*/
	/*int w1[NUM_NODES][NUM_NODES] = {
		{0,1,1,0,0,0,0,0,0},
		{1,0,1,1,1,0,0,0,0},
		{1,1,0,0,0,1,1,0,0},
		{0,1,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,1},
		{0,0,1,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0}
	};*/
	/*int w1[NUM_NODES][NUM_NODES] = {
		{0,0,1,0,1,0},
		{0,0,0,0,0,1},
		{0,1,0,1,0,1},
		{0,0,0,0,0,1},
		{0,0,0,0,0,1},
		{0,0,0,0,0,0}
	};*/
	int dsex2[NUM_NODES][NUM_NODES] =
	{
		{0,1,1,0,0,0,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0}
	};
	int dist[NUM_NODES];

	bool selected[NUM_NODES] = { false, };
	dfsStack(dsex2, selected, 0);
	printf("\n");
	bool selected1[NUM_NODES] = { false, };
	bfs(dsex2, selected1, 0);
	return 0;
}