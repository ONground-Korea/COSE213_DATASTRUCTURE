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
	int index = 0;
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
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (w[i][j] == 0) w[i][j] = INF; // �̾����� ���� �͵��� INF�� �ʱ�ȭ
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
	int edge_accpted = 0;// ������� ���õ� ���� ��
	int uset, vset; // ���� u�� v�� ���� ��ȣ
	edge e;
	int sum = 0;

	for (int i = 0; i < MAX_VERTICES; i++) //parent �迭 �ʱ�ȭ
		parent[i] = i;

	qsort(g->edges, g->vertices, sizeof(edge), compare); // ���� ����ġ ���� ������� ����

	for (int i = 0; edge_accpted < g->nodes - 1; i++)
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
	int w1[10][10] = {
		{0, 6, 3, 0, 9,   0, 0, 0, 0, 0},
		{6, 0, 4, 2, 0,   0, 0, 9, 0, 0},
		{3, 4, 0, 2, 9,   9, 0, 0, 0, 0},
		{0, 2, 2, 0, 0,   8, 0, 9, 0, 0},
		{9, 0, 9, 0, 0,   8, 0, 0, 0, 18},
		{0, 0, 9, 8, 8,   0, 9, 7, 0, 10},
		{0, 0, 0, 0, 0,   9, 0, 5, 1, 3},
		{0, 9, 0, 9, 0,   7, 5, 0, 4, 0},
		{0, 0, 0, 0, 0,   0, 1, 4, 0, 4},
		{0, 0, 0, 0, 18,  10, 3, 0, 4, 0}
	};
	int dist[NUM_NODES];
	printf("prim::\n");
	prim(w, 0, dist);
	printf("\n========================================\n\n");

	graph* g = (graph*)malloc(sizeof(graph));
	g->vertices = 0;
	g->nodes = NUM_NODES;
	int tc = 0;
	for (int i = 0; i < NUM_NODES; i++) //graph �Է�
	{
		for (int j = i + 1; j < NUM_NODES; j++)
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

/*
#include<stdio.h>

#include<stdlib.h>

#define MAX_VER 100



int parent[MAX_VER];

int num[MAX_VER];





// �ʱ�ȭ �Լ�

void init_set(int n) {

		  int i;

		  for (i = 0; i < n; i++) {

				   //- : ����, ������ ���� : ������ ����, ����� �� : ������ �θ�

				   parent[i] = -1;

				   // �� �������� ������ ����

				   num[i] = 1;

		  }

}



//������ ��Ʈ ��带 ã�ư��� ����Ŭ�� �����Ǵ��� Ȯ���ϱ����� �Լ�

int find_set(int vertex) {

		  int whatp, p, i = -1;

		  for (i = vertex; (whatp = parent[i]) >= 0; i = whatp)

				   ;    // ������ parent�� ã�ư�

		  p = i; //parent�� �߰��س�.

		  for (i = vertex; (whatp = parent[i]) >= 0; i = whatp)

				   parent[i] = p;  // ������ parent

		  return p;

}



//����Ŭ�� �������� �ʴ� �ΰ��� Ʈ�������� ����

//�� ���ڰ� �� ���� ���� ū ���� �ڽ����� ���� ���� ����.

void union_set(int r1, int r2) {



		  if (num[r1] < num[r2]) {

				   parent[r1] = r2;   //r2 = �θ��尡 �ɰ�  r1  = �ڽ�

				   num[r2] += num[r1]; // r2�� ������ r1�� ������ ������ŭ ��.

		  }

		  else {

				   parent[r2] = r1;

				   num[r1] += num[r2];

		  }

}



typedef struct {

		  int src;

		  int dest;

		  int weight;

}forSort;



 //�������� ������ ���� �Լ� -->qsort���� ���� 

int compare(const void* a, const void* b) {

	const forSort* m1 = (const forSort*)a;

	const forSort* m2 = (const forSort*)b;



	return m1->weight - m2->weight;

}



void kruskal(int cost[9][9]) {



	int i, j;

	int index = 0;

	int edge_count = 0;

	int min, mincost = 0;

	int uset, vset; //���� u�� ���� v�� ���� ��ȣ

	forSort arr[MAX_VER] = { 0 };



	for (i = 0; i < 9; i++) {

		for (j = 0; j < 9; j++) {

			if (cost[i][j] != 0) {

				arr[index].weight = cost[i][j];

				cost[j][i] = 0;

				arr[index].src = i;     // �ش� ����ġ�� ���� 2���� ����ϱ����� �迭

				arr[index].dest = j;

				index++;

			}

		}

	}

	qsort(arr, index, sizeof(forSort), compare);  //-->tmp_arr�迭�� ����� ����ġ�� ������������ ����



	for (i = 0; i < index; i++) {     // --> qsortȮ��

		printf("%d\n", arr[i].weight);

	}



	init_set(9);

	i = 0;

	while (edge_count < (9 - 1)) {

		if (i < index) {

			min = arr[i].weight;

			uset = find_set(arr[i].src);

			vset = find_set(arr[i].dest);



			if (uset != vset) {

				edge_count++;

				union_set(uset, vset);

				mincost += min;

				printf("������ ����ġ: %d\t-->", min);

				printf("���� �ּҰ� : %d\n", mincost);

			}

			i++;

		}

	}

	printf("\n�ּҰ� : %d \n", mincost);

}





int main() {





	int graph[9][9] = {                 // input_graph.pptx�� ���� ����������.

			 {0, 4, 0, 0, 0, 0, 0, 8, 0},

			 {4, 0, 8, 0, 0, 0, 0, 11, 0},

			 {0, 8, 0, 7, 0, 4, 0, 0, 2},

			 {0, 0, 7, 0, 9, 14, 0, 0, 0},

			 {0, 0, 0, 9, 0, 10, 0, 0, 0},

			 { 0, 0, 4, 14, 10, 0, 2, 0, 0},

			 { 0, 0, 0, 0, 0, 2, 0, 1, 6},

			 { 8, 11, 0, 0, 0, 0, 0, 0, 7},

			 { 0, 0, 2, 0, 0, 0, 6, 7, 0 },

	};





	kruskal(graph);



}*/