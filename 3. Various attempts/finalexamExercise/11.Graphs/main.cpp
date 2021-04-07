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
	final static int infi = 999;  // ������ ���� ����, ����ġ ���Ѵ븦 ����.

	public static void dijkstra(int[][] c, int n, int[][] t, int vertex) {
		//c�迭�� �׷����� �������, n�� ������ ����, t�迭�� ����� �����迭, vertex�� ���� ����
		int[] from = new int[n]; // �� ������ ��� �������κ��� ����Ǿ����� ǥ���ϴ� �迭
		int[] dist = new int[n]; //������� ������ ���������� �� ���������� ����ġ�� ǥ��

		for (int i = 0; i < n; i++) { // ���� ���������� ù��° ���������� vertex���� �ʱ�ȭ
			from[i] = vertex;
			dist[i] = c[vertex][i];
		}

		int best = 0;
		for (int i = 0; i < n - 1; i++) { //n-1�� ����� ������ �� 
			best = isBest(dist); // dist�迭�� 0�� ������ �ּҰ��� ���� ������ �ε���
			t[0][i] = from[best]; // ����ġ�� ���� ���� ������ �����ؼ� �־��ش�. 
			t[1][i] = best;

			for (int j = 0; j < n; j++) { // dist�迭�� from�迭�� �ֽ�ȭ
				if (dist[best] + c[best][j] < dist[j]) { // �ֱٿ� ���õ� ������ ������ ������ ����ġ�� ���� dist�迭�� ��
					from[j] = best;
					dist[j] = dist[best] + c[best][j];
				}
			}
			dist[best] = 0; // �κ� �׷����� ���õ� ���������� ����ġ�� 0���� ����
		}
	}

	public static int isBest(int[] dist) { // dist�迭�� 0�� ������ �ּҰ��� ���� ������ �ε����� ��ȯ�ϴ� �޼ҵ�
		int best = 0;

		for (int i = 0; i 0) {
			best = i;
			break;
		}
	}

	for (int j = 0; j < dist.length; j++) { // dist���� 0�̾ƴ� �� �� ���� ���� ���� �ε����� ã�´�.
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
	printf("selected: %d (%d)\n", 1, dist[0]); //ó�� ���� ���
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
		printf("selected: %d (%d)\n", cur + 1, dist[cur]); //���� ���
		for (int i = 0; i < NUM_NODES; i++)
		{
			if (dist[i] != INF) printf("%d ", dist[i]);
			else printf("X ");
		}
		printf("\n");//
	}
	printf("selected: %d (%d)\n", NUM_NODES, dist[NUM_NODES - 1]);//������ ���� ���
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