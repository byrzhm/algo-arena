#include <bits/stdc++.h>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace slow {

class Solution {
 public:
  int diameterOfBinaryTree(TreeNode *root) {
    if (root == nullptr) return 0;

    diameterOfBinaryTree(root->left);
    diameterOfBinaryTree(root->right);

    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    diameter = std::max(leftDepth + rightDepth + 1, diameter);

    return diameter;
  }

 private:
  int depth(TreeNode *root) {
    if (root == nullptr) return 0;

    return std::max(depth(root->left), depth(root->right)) + 1;
  }

  int diameter;
};

}  // namespace slow

namespace fast {

class Solution {
 public:
  int diameterOfBinaryTree(TreeNode *root) {
    maxDiameter = 0;
    dfs(root);
    return maxDiameter;
  }

 private:
  int dfs(TreeNode *root) {
    if (root == nullptr) return -1;

    int l = dfs(root->left);
    int r = dfs(root->right);

    maxDiameter = std::max(maxDiameter, l + r + 2);
    return std::max(l, r) + 1;
  }

  int maxDiameter;
};

}  // namespace fast