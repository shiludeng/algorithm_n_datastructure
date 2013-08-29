#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_NODES = 110;

struct TreeNode {
	int childNum;
	int *childs;
	int value;
};


TreeNode nodes[MAX_NODES];
vector<vector<int> > res;
int N, M, S;

int cmp(const void *a, const void *b) {
	return nodes[*((int*) b)].value - nodes[*((int*) a)].value;
}

void dfs(int nodeNum, vector<int> &path, int &sum) {
	if (sum > S)
		return;
	if (sum == S && nodes[nodeNum].childNum == 0) {
		vector<int> v(path);
		res.push_back(v);
		return;
	}

	int childNum = nodes[nodeNum].childNum;
	for (int i = 0; i < childNum; i++) {
		int child = nodes[nodeNum].childs[i];
		sum += nodes[child].value;
		path.push_back(nodes[child].value);
		dfs(child, path, sum);
		sum -= nodes[child].value;
		path.pop_back();
	}
}

int main() {
	int tmpChild[MAX_NODES];
	while (scanf("%d %d %d", &N, &M, &S) != -1) {
		for (int i = 0; i < N; i++) {
			nodes[i].childNum = 0;
			scanf("%d", &nodes[i].value);
		}
		for (int i = 0; i < M; i++) {
			int nonLeafNode, childNum;
			scanf("%d%d", &nonLeafNode, &childNum);
			for (int j = 0; j < childNum; j++) {
				scanf("%d", &tmpChild[j]);
			}
			qsort(tmpChild, childNum, sizeof(int), cmp);
			//for (int j = 0; j < childNum; j++) {
				//printf("%d ", tmpChild[j]);
			//}
			//printf("\n");
			nodes[nonLeafNode].childs = new int[childNum];
			nodes[nonLeafNode].childNum = childNum;
			for (int j = 0; j < childNum; j++) {
				nodes[nonLeafNode].childs[j] = tmpChild[j];
			}
		}
		
		//printf("result: \n\n");
		res.clear();
		vector<int> v(1, nodes[0].value);
		int sum = nodes[0].value;
		dfs(0, v, sum);

		for (int i = 0; i < res.size(); i++) {
			for (int j = 0; j < res[i].size() - 1; j++) {
				printf("%d ", res[i][j]);	
			}
			if (res[i].size() - 1 >= 0) {
				printf("%d\n", res[i][res[i].size() - 1]);
			}
		}
	}
	return 0;
}
