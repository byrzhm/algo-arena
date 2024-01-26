#include <bits/stdc++.h>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int kthSmallest(TreeNode *root, int k) {
    std::stack<TreeNode *> stack;
    // int count = 0;

    while (!stack.empty() || root != nullptr) {
      while (root != nullptr) {  // 一直向左走
        stack.push(root);
        root = root->left;
      }

      root = stack.top();  // 到达最左边的节点
      stack.pop();

      // 中序遍历
      // ++count;
      // if (count == k) {
      //   return root->val;
      // }
      if (--k == 0) {
        return root->val;
      }

      root = root->right;  // 转向右子树
    }
    return {};
  }
};