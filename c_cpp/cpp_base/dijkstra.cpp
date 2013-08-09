#include <stdio.h>
#include <vector>

using namespace std;

const int MAX_DIST = 100000;

int dijkstra(vector<vector<int> > edges, vector<int> &path, int n, 
			int src, int dst) {
	vector<int> dist(n);
	vector<bool> visited(n);

	for (int i = 0; i < n; i++) {
		dist[i] = edges[src][i];
		visited[i] = false;
		path[i] = 0;
	}
	
	visited[src] = true;
	for (int i = 1; i < n; i++) {
		int tmp = MAX_DIST;
		int k = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && dist[j] < tmp) {
				tmp = dist[j];
				k = j;
			}
		}
		
		visited[k] = true;
		for (int i = 0; i < n; i++) {
			if(!visited[i] && dist[k] + edges[k][i] < dist[i]) {
				dist[i] = dist[k] + edges[k][i];
				path[i] = k;
			}
		}
	}
	return dist[dst];
}

void printPath(vector<int> path, int n) {
	if (path[n] == 0) {
		printf("0->%d", n);
		return;
	}

	printPath(path, path[n]);
	printf("->%d", n);
}

int main() {
	int m, n;
	
	while (true) {
		printf("input the number of vertex & the number of edges: ");
		if (scanf("%d %d", &m, &n) == - 1) {
			break;
		}

		vector<vector<int> > edges(m);
		for (int i = 0; i < m; i++) {
			edges[i].resize(m);
			for (int j = 0; j < m; j++) {
				edges[i][j] = MAX_DIST;
				if (i == j) {
					edges[i][j] = 0;
				}
			}
		}
		while(n--) {
			int start, end, len;
			scanf("%d %d %d", &start, &end, &len);
			edges[start][end] = len;
			edges[end][start] = len;
		}

		vector<int> path(m);
		int res = dijkstra(edges, path, m, 0, m - 1);	
		printf("from node %d to node %d: %d\n", 0, m - 1, res);
		printPath(path, m - 1);
		printf("\n");
	}
}
