#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
// Number of vertices in the graph 
#define V 5

// A utility function to print the  
// constructed MST stored in parent[]
// This function can be customized as you want
int printMST(int parent[], int n, int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[V][V]) {
    /*
     * Prim's algorithm
     */
#define INF 99999
	bool selected[V] = { false, };
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (graph[i][j] == 0) graph[i][j] = INF; // 이어지지 않은 것들을 INF로 초기화

	int dist[V];
	for (int i = 0; i < V; i++)
		dist[i] = INF;
	dist[0] = 0;

	int parent[V] = { 0, };

	for (int i = 0; i < V; i++)
	{
		int cur = 0;
		for (int j = 0; j < V; j++)
		{
			if (!selected[j])
			{
				cur = j;
				break;
			}
		}
		for (int j = 0; j < V; j++)
		{
			if (!selected[j] && (dist[j] < dist[cur]))
				cur = j;
		}

		selected[cur] = true;
		if (dist[cur] == INF) return;

		for (int j = 0; j < V; j++)
		{
			if (graph[cur][j] != INF)
			{
				if (!selected[j] && graph[cur][j] < dist[j])
				{
					dist[j] = graph[cur][j];
					parent[j] = cur;
				}
			}
		}
		
		//printf("vertex %d(%d weight) included\n", cur, dist[cur]);
	}
	printMST(parent, V, graph);
}


int main() {
    int graph[V][V] = { {0, 2, 0, 6, 0},
                       {2, 0, 3, 8, 5},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {0, 5, 7, 9, 0} };

    // Print the solution 
    primMST(graph);

    return 0;
}