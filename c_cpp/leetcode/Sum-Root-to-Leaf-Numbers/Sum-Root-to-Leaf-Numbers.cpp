#include <stdio.h>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {

	}
};

/*
 * Run Status: Accepted
 * Program Runtime:
 * 	small data: 0ms
 *	large data: 24ms
 */
class Solution {
private:
	int sum;
	void dfs(TreeNode *root, int sum) {
		if (root == NULL) {
			return;
		}
		if (root->left == NULL && root->right == NULL) {
			this->sum += (sum * 10) + root->val;
			return;
		}

		sum = sum * 10 + root->val; 
		dfs(root->left, sum);
		dfs(root->right, sum);
	}
public:
	int sumNumbers(TreeNode *root) {
		sum = 0;
		dfs(root, sum);
		return sum;
	}
};

TreeNode* buildTree() {
	int val;
	printf("input the value of root node: ");
	scanf("%d", &val);
	if (val < 0) 
		return NULL;
	
	TreeNode *root = new TreeNode(val);
	printf("build left child: \n");
	root->left = buildTree();
	printf("build right child: \n");
	root->right = buildTree();
	return root;
}

int main() {
	Solution solution;

	TreeNode *root;
	printf("build tree:\n");
	while (root = buildTree()) {
		printf("%d\n", solution.sumNumbers(root));	
		printf("build tree:\n");
	}
	return 0;
}
