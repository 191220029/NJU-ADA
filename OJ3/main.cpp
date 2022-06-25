#include<iostream>

using namespace std;

int n;
int* preorder, * inorder;
int diameter;



struct TreeNode {
	int val;
	TreeNode* left, * right;
	TreeNode(int _val = 0) {
		val = _val;
		left = right = NULL;
	}
}*Root;

int Find(int *vec, int target) {
	int i = 0;
	for (; i < n; i++) {
		if (target == vec[i]) return i;
	}
	return -1;
}

TreeNode* buildChild(int left_pre, int right_pre, int left_in, int right_in) {
	if (left_pre > right_pre || left_in > right_in) return NULL;
	TreeNode* root = new TreeNode(preorder[left_pre]);
	if (left_pre == right_pre) return root;
	int rootPos = Find(inorder, root->val);
	int size_left = rootPos - left_in;
	root->left = buildChild(left_pre + 1, left_pre + size_left, left_in, rootPos - 1);
	root->right = buildChild(left_pre + size_left + 1, right_pre, rootPos + 1, right_in);
	return root;
}

int TreeHeight(TreeNode* root) {
	if (!root) return 0;
	int leftH = TreeHeight(root->left);
	int rightH = TreeHeight(root->right);
	diameter = max(diameter, leftH + rightH);
	return max(leftH, rightH) + 1;
}

int main() {
	cin >> n;
	preorder = new int[n], inorder = new int[n];
	for (int i = 0; i < n; i++)
		scanf("%d", preorder + i);
	for (int i = 0; i < n; i++)
		scanf("%d", inorder + i);

	Root = buildChild(0, n - 1, 0, n - 1);
	int h = 0;
	if (Root) 
		h = TreeHeight(Root) - 1;
	printf("I have read the rules about plagiarism punishment\n");
	
	cout << h << endl;
	cout << diameter << endl;
	return 0;
}
/*
10
0 1 9 3 8 4 2 7 5 6
3 9 8 1 2 4 0 5 7 6

0


1
1
1

2
1 2
1 2

3
1 2 3
2 1 3

3
1 2 3
3 2 1
*/