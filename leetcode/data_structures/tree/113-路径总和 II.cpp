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
  std::vector<std::vector<int>> pathSum(TreeNode *root, int targetSum) {
    if (root == nullptr) return {};
    backtracking(root, targetSum);
    return solutions;
  }

 private:
  void backtracking(TreeNode *root, int targetSum) {
    if (root == nullptr) {
      return;
    }

    targetSum = targetSum - root->val;
    solution.push_back(root->val);

    if (root->left == nullptr && root->right == nullptr && targetSum == 0) {  // leaf node
      solutions.emplace_back(solution);
    }

    backtracking(root->left, targetSum);
    backtracking(root->right, targetSum);

    solution.pop_back();
  }

  std::vector<int> solution;
  std::vector<std::vector<int>> solutions;
};