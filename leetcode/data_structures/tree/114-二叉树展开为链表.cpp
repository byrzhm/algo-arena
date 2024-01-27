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
  void flatten(TreeNode *root) {
    if (root == nullptr) return;
    dfs(root);
  }

 private:
  std::pair<TreeNode *, TreeNode *> dfs(TreeNode *root) {
    if (root->left == nullptr && root->right == nullptr) {
      return {root, root};
    }

    if (root->left == nullptr) {
      auto [rup, rdown] = dfs(root->right);
      return {root, rdown};
    }

    if (root->right == nullptr) {
      auto [lup, ldown] = dfs(root->left);
      root->left = nullptr;
      root->right = lup;
      return {root, ldown};
    }

    auto [lup, ldown] = dfs(root->left);
    auto [rup, rdown] = dfs(root->right);
    root->left = nullptr;
    root->right = lup;
    ldown->right = rup;
    return {root, rdown};
  }
};