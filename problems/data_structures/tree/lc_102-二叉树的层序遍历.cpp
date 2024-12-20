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
  std::vector<std::vector<int>> levelOrder(TreeNode *root) {
    std::vector<std::vector<int>> results;
    std::vector<int> levelVals;

    std::queue<TreeNode *> queue;
    queue.push(root);

    while (!queue.empty()) {
      int size = queue.size();
      levelVals.reserve(size);
      for (int i = 0; i < size; ++i) {
        TreeNode *node = queue.front();
        queue.pop();

        if (node != nullptr) {
          levelVals.emplace_back(node->val);
          queue.push(node->left);
          queue.push(node->right);
        }
      }

      if (!levelVals.empty()) {
        results.emplace_back();
        results.back().swap(levelVals);  // improve performance
      }
    }
    return results;
  }
};