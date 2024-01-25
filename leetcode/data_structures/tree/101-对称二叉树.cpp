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
  bool isSymmetric(TreeNode *root) {
    if (root == nullptr) return true;

    return isSymmetricInternal(root->left, root->right);
  }

 private:
  bool isSymmetricInternal(TreeNode *left, TreeNode *right) {
    if (left == nullptr && right == nullptr) {
      return true;
    }

    if (left == nullptr || right == nullptr) {
      return false;
    }

    return left->val == right->val && isSymmetricInternal(left->left, right->right) &&
           isSymmetricInternal(left->right, right->left);
  }
};