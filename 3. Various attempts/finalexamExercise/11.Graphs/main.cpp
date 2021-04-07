#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_NODES 6
#define INF 0x7FFF

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
int choose(int(*w)[NUM_NODES], int(*dist), bool found[])
{
	int cur = 0;
	int min = INF;
	for (int i = 0; i < NUM_NODES; i++)
	{
		if (!found[i] && dist[i] < min)
		{
			min = dist[i];
			cur = i;
		}
	}
	return cur;
}
/*
public class DijkstraSP {
	final static int infi = 999;  // 연결이 되지 않음, 가중치 무한대를 뜻함.

	public static void dijkstra(int[][] c, int n, int[][] t, int vertex) {
		//c배열은 그래프의 인접행렬, n은 정점의 개수, t배열은 연결된 간선배열, vertex는 시작 정점
		int[] from = new int[n]; // 각 정점이 어느 정점으로부터 연결되었는지 표시하는 배열
		int[] dist = new int[n]; //현재까지 결정된 목적지에서 각 정점마다의 가중치를 표시

		for (int i = 0; i < n; i++) { // 최초 시작정점은 첫번째 정점임으로 vertex으로 초기화
			from[i] = vertex;
			dist[i] = c[vertex][i];
		}

		int best = 0;
		for (int i = 0; i < n - 1; i++) { //n-1은 연결될 간선의 수 
			best = isBest(dist); // dist배열중 0을 제외한 최소값을 가진 원소의 인덱스
			t[0][i] = from[best]; // 가중치가 가장 적은 간선을 선택해서 넣어준다. 
			t[1][i] = best;

			for (int j = 0; j < n; j++) { // dist배열과 from배열의 최신화
				if (dist[best] + c[best][j] < dist[j]) { // 최근에 선택된 정점에 인접한 정점에 가중치와 기존 dist배열과 비교
					from[j] = best;
					dist[j] = dist[best] + c[best][j];
				}
			}
			dist[best] = 0; // 부분 그래프로 선택된 정점까지의 가중치는 0으로 변경
		}
	}

	public static int isBest(int[] dist) { // dist배열중 0을 제외한 최소값을 가진 원소의 인덱스를 반환하는 메소드
		int best = 0;

		for (int i = 0; i 0) {
			best = i;
			break;
		}
	}

	for (int j = 0; j < dist.length; j++) { // dist에서 0이아닌 값 중 값이 가장 작은 인덱스를 찾는다.
		if (dist[j] != 0 && dist[j] < dist[best]) {
			best = j;
		}
	}

	return best;
}

public static void main(String[] args) {
	int[][] graph = {
			{0,8,7,20,14,infi},
			{infi, 0, infi, 13, infi, infi},
			{infi, infi, 0, infi, 5, infi},
			{12, infi, infi, 0,infi, infi},
			{11, infi, infi, 6, 0, 4},
			{infi, infi, infi, 10, infi, 0},
	};
	int[][] t = new int[2][5];

	dijkstra(graph, 6, t, 0);

	for (int i = 0; i < t[0].length; i++) {
		System.out.println(t[0][i] + 1 + " " + (t[1][i] + 1));
	}
}
}
*/
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
		int cur = choose(w, dist, found);
		found[cur] = true;

		for (int j = 0; j < NUM_NODES; j++)
		{
			if (!found[j])
			{
				if (dist[cur] + w[cur][j] < dist[j])
				{
					dist[j] = dist[cur] + w[cur][j];
				}
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
	printf("selected: %d (%d)\n", NUM_NODES, dist[NUM_NODES - 1]);//마지막 과정 출력
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
	int w1[NUM_NODES][NUM_NODES] = {
			{0,8,7,20,14,INF},
			{INF, 0, INF, 13, INF, INF},
			{INF, INF, 0, INF, 5, INF},
			{12, INF, INF, 0,INF, INF},
			{11, INF, INF, 6, 0, 4},
			{INF, INF, INF, 10, INF, 0}
	};

	int dist[NUM_NODES];

	dijkstra(w1, dist);
	bool selected[NUM_NODES] = { false, };
	dfs(w1, selected,0);

	return 0;
}