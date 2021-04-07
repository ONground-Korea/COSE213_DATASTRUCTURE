#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_NODE 	9
#define INF 		0x7FFF

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
int Pa(int* arr, int sum, int x, int graph[NUM_NODE][NUM_NODE])
{
	if (arr[x] == x) return sum;
	sum += graph[x][arr[x]];
	Pa(arr, sum, arr[x], graph);

}
// Write distances from the 'a' node to other nodes in 'distOut' parameter.
void exePrim(int* distOut, int(*w)[NUM_NODE], int startNode)
{
	// TODO
	bool selected[NUM_NODE] = { false, };
	int dist[NUM_NODE];
	int parent[NUM_NODE] = { 0, };
	for (int i = 0; i < NUM_NODE; i++)
		dist[i] = INF;
	dist[startNode] = 0;

	for (int i = 0; i < NUM_NODE; i++)
	{
		int cur = get_min_vertex(NUM_NODE, selected, dist);
		selected[cur] = true;
		if (dist[cur] == INF) return;

		for (int j = 0; j < NUM_NODE; j++)
		{
			if (w[cur][j] != INF)
			{
				if (!selected[j] && w[cur][j] < dist[j])
				{
					dist[j] = w[cur][j];
					parent[j] = cur;
				}
			}
		}
	}
	for (int i = 0; i < NUM_NODE; i++)
	{
		distOut[i] = Pa(parent, 0, i, w);
	}
	
}

int main()
{
	// Given graph
	int wIn[NUM_NODE][NUM_NODE] = {
		{ 0,	4,		INF,	INF,	INF,	INF,	INF,	8,		INF	},
		{ 4,	0,		8,		INF,	INF,	INF,	INF,	11,		INF },
		{ INF,	8,		0,		7,		INF,	4,		INF,	INF,	2	},
		{ INF,	INF,	7,		0,		9,		14,		INF,	INF,	INF },
		{ INF,	INF,	INF,	9,		0,		10,		INF,	INF,	INF },
		{ INF,	INF,	4,		14,		10,		0,		2,		INF,	INF },
		{ INF,	INF,	INF,	INF,	INF,	2,		0,		1,		6	},
		{ 8,	11,		INF,	INF,	INF,	INF,	1,		0,		7	},
		{ INF,	INF,	2,		INF,	INF,	INF,	6,		7,		0	}
	};

	int distExpect[NUM_NODE] = { 0, 4, 12, 19, 28, 16, 18, 19, 14 };
	int dist[NUM_NODE];

	// Init dist as INF
	for (int i = 0; i < NUM_NODE; i++)
	{
		dist[i] = INF;
	}

	int startNode = 0;				// start from 'a'
	exePrim(dist, wIn, startNode);	// execute prim algorithm

	//////////////////////////////
	// Test result
	for (int i = 0; i < NUM_NODE; ++i)
	{
		printf("%c: ", i + 'a');
		if (dist[i] == distExpect[i])
		{
			printf("PASS\n");
		}
		else
		{
			printf("FAIL\n");
		}
	}
	//////////////////////////////

	return 0;
}
