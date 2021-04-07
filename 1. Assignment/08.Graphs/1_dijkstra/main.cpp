#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_NODES 6
#define INF 0x7FFF

void dijkstra(int(*w)[NUM_NODES], int(*dist))
{
	// TODO

	bool found[NUM_NODES] = { false, };
	for (int i = 0; i < NUM_NODES; i++)
		dist[i] = w[0][i];

	dist[0] = 0;
	found[0] = true;
	printf("selected: %d (%d)\n", 1, dist[0]); //처음 과정 출력
	for (int i = 0; i < NUM_NODES; i++)
	{
		if (dist[i] != INF) printf("%d ", dist[i]);
		else printf("X ");
	}
	printf("\n");//

	for (int i = 0; i < NUM_NODES - 2; i++)
	{
		int index = 0;
		int min = INF;
		for (int i = 0; i < NUM_NODES; i++) // choose함수(가중치 가장 작은, 포함시키지 않은 인접 노드 선택)
		{
			if (dist[i] < min && !found[i])
			{
				min = dist[i];
				index = i;
			}
		}//
		int cur = index;
		found[cur] = true;
		
		for (int j = 0; j < NUM_NODES; j++)
		{
			if (!found[j])
			{
				if (dist[cur] + w[cur][j] < dist[j])
					dist[j] = dist[cur] + w[cur][j];
			}
		}
		printf("selected: %d (%d)\n", cur + 1, dist[cur]); //과정 출력
		for (int i = 0; i < NUM_NODES; i++)
		{
			if (dist[i] != INF) printf("%d ", dist[i]);
			else printf("X ");
		}
		printf("\n");//
	}
	printf("selected: %d (%d)\n", NUM_NODES, dist[NUM_NODES-1]);//마지막 과정 출력
	for (int i = 0; i < NUM_NODES; i++)
	{
		if (dist[i] != INF) printf("%d ", dist[i]);
		else printf("X ");
	}
	printf("\n");//

	printf("------------------------------\n");
	printf("Results::\n");
	for (int i = 1; i < NUM_NODES; ++i)
	{
		printf("To %d: %d\n", i+1, dist[i]);
	}
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
	dijkstra(w, dist);

	/* NUM_NODES 값을 5로 변경후 실행.
	int ex2[5][5] = {  // other graph type (Example graph 2)
		{INF, 10, INF, 30, 100},
		{10, INF, 50, INF, INF},
		{INF, 50, INF, 20, 10},
		{30, INF, 20, INF, 60},
		{100, INF, 10, 60, INF}
	};
	int dist2[5];
	dijkstra(ex2, dist2)
	*/
	return 0;
}