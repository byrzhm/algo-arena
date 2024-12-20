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
  std::vector<int> inorderTraversal(TreeNode *root) {
    internalInorderTraversal(root);
    return seq;
  }

 private:
  void internalInorderTraversal(TreeNode *root) {
    if (root != nullptr) {
      internalInorderTraversal(root->left);
      seq.emplace_back(root->val);
      internalInorderTraversal(root->right);
    }
  }

  std::vector<int> seq;
};