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
  bool hasPathSum(TreeNode *root, int targetSum) {
    if (root == nullptr) return false;
    return dfs(root, targetSum);
  }

 private:
  bool dfs(TreeNode *root, int targetSum) {
    int newTargetSum = targetSum - root->val;
    if (root->left == nullptr && root->right == nullptr) {  // leaf node
      return newTargetSum == 0;
    }

    if (root->left == nullptr) {
      return dfs(root->right, newTargetSum);
    }

    if (root->right == nullptr) {
      return dfs(root->left, newTargetSum);
    }

    return dfs(root->left, newTargetSum) || dfs(root->right, newTargetSum);
  }
};