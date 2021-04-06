#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_NODES 6
#define INF 0x7FFF
#define MAX_VERTICES 100

typedef struct Edge {
	int start, end, weight;
}edge;
typedef struct Graph {
	int vertices;
	int nodes;
	edge edges[2 * MAX_VERTICES];
}graph;

int compare(const void* a, const void* b)
{
	edge* x = (edge*)a;
	edge* y = (edge*)b;
	return (x->weight - y->weight);
}

int get_min_vertex(int n, bool selected[], int dist[])
{
	int index=0;
	for (int i = 0; i < n; i++)
	{
		if (!selected[i])
		{
			index = i;
			break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (!selected[i] && (dist[i] < dist[index]))
			index = i;
	}

	return index;
}

void prim(int(*w)[NUM_NODES], int startPoint, int dist[])
{
	bool selected[NUM_NODES] = { false, };
	for (int i = 0; i < NUM_NODES; i++)
		dist[i] = INF;
	dist[startPoint] = 0;

	for (int i = 0; i < NUM_NODES; i++)
	{
		int cur = get_min_vertex(NUM_NODES, selected, dist);
		selected[cur] = true;
		if (dist[cur] == INF) return;

		for (int j = 0; j < NUM_NODES; j++)
		{
			if (w[cur][j] != INF)
			{
				if (!selected[j] && w[cur][j] < dist[j])
					dist[j] = w[cur][j];
			}
		}
		printf("vertex %d(%d weight) included\n", cur, dist[cur]);
		/*printf("selected: %d (%d)\n", cur, dist[cur]); //과정 출력
		for (int i = 0; i < NUM_NODES; i++)
		{
			if (dist[i] != INF) printf("%d ", dist[i]);
			else printf("%c ", 'X');
		}
		printf("\n\n");//*/
	}

	printf("------------------------------\n");
	int sum = 0;
	for (int i = 0; i < NUM_NODES; i++)
		sum += dist[i];
	printf("Sum: %d", sum);
}

int getParent(int arr[], int x)
{
	if (arr[x] == x) return x;
	return arr[x] = getParent(arr, arr[x]);
}

void Union(int arr[], int a, int b)
{
	a = getParent(arr, a);
	b = getParent(arr, b);
	if (a < b) arr[b] = a;
	else arr[a] = b;
}

bool find(int arr[], int a, int b)
{
	a = getParent(arr, a);
	b = getParent(arr, b);
	if (a == b) return true;
	else return false;
}

int parent[MAX_VERTICES];

void kruskal(graph* g)
{
	int edge_accpted = 0;// 현재까지 선택된 간선 수
	int uset, vset; // 정점 u와 v의 집합 번호
	edge e;
	int sum = 0;

	for (int i = 0; i < MAX_VERTICES; i++) //parent 배열 초기화
		parent[i] = i;

	qsort(g->edges, g->vertices, sizeof(edge), compare); // 간선 가중치 적은 순서대로 정렬

	for (int i = 0; edge_accpted < g->nodes-1; i++)
	{
		e = g->edges[i];
		if (!find(parent, e.start, e.end))
		{
			printf("edge (%d-%d) %d(weight) included\n", e.start, e.end, e.weight);
			edge_accpted++;
			sum += e.weight;
			Union(parent, e.start, e.end);
		}
	}
	printf("------------------------------\n");
	printf("Sum: %d", sum);
}

int main()
{
	int w[NUM_NODES][NUM_NODES] = {
		{0,		6,		3,		INF,	INF,	INF},
		{6,		0,		2,		5,		INF,	INF},
		{3,		2,		0,		3,		4,		INF},
		{INF,	5,		3,		0,		2,		3},
		{INF,	INF,	4,		2,		0,		5},
		{INF,	INF,	INF,	3,		5,		0}
	};
	int dist[NUM_NODES];
	printf("prim::\n");
	prim(w, 0, dist);
	printf("\n========================================\n\n");

	graph* g = (graph*)malloc(sizeof(graph));
	g->vertices = 0;
	g->nodes = NUM_NODES;
	int tc = 0;
	for (int i = 0; i < NUM_NODES; i++) //graph 입력
	{
		for (int j = i+1; j < NUM_NODES; j++)
		{
			g->edges[tc].start = i;
			g->edges[tc].end = j;
			g->edges[tc].weight = w[i][j];
			tc++;
			g->vertices++;
		}
	}
	//
	printf("kruskal::\n");
	kruskal(g);
	free(g);
	return 0;
}