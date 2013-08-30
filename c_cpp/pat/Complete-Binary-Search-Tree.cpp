#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    Node *left;
    Node *right;
    int value;
};

const int max_nodes = 1010;
const double eps = 1e-6;
int ele[max_nodes];
int res[max_nodes];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int getTreeHeight(int n) {
    double res = log(n + 1) / log(2);
    if (abs(res - (int) res) <= eps) 
        return (int)res;
    return 1 + (int)res;
}

void buildTree(Node **root, int *ele, int len) {
    if (len == 0) {
		*root = NULL;
        return;
	}

	int h = getTreeHeight(len);
    if (h == 1) {
        *root = new Node;
		(*root)->value = ele[0];
        (*root)->right = NULL;
        (*root)->left = NULL;
        return;
	}

    int rootPos;
	if (getTreeHeight(len - pow(2, h - 1)) == h - 1) {
        rootPos = pow(2, h - 1) - 1;
	} else {
        rootPos = len - pow(2, h - 2);
	}
    
    *root = new Node;
    (*root)->value = ele[rootPos];
	buildTree(&(*root)->right, ele + rootPos + 1, len - 1 - rootPos);
    buildTree(&(*root)->left, ele, rootPos);
}

void travel(Node *root) {
    if (NULL == root)
        return;

    queue<Node*> q;
	q.push(root);
    int t = 0;
	while (!q.empty()) {
		Node *tp = q.front();
		res[t++] = tp->value;
        q.pop();
		if (tp->left)
			q.push(tp->left);
		if (tp->right)
			q.push(tp->right);
	}
}

/*

10
1 2 3 4 5 6 7 8 9 0

 */
int main() {
    int n;
    while (scanf("%d", &n) != -1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &ele[i]);
		}
		qsort(ele, n, sizeof(int), cmp);

        Node *root;
        buildTree(&root, ele, n);

		travel(root);
        for (int i = 0; i < n - 1; i++) {
            printf("%d ", res[i]);
		}
        printf("%d\n", res[n-1]);
	}
    return 0;
}