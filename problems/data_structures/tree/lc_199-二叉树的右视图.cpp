#include <bits/stdc++.h>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace dfs {

class Solution {
 public:
  std::vector<int> rightSideView(TreeNode *root) {
    dfs(root, 0);
    return ans;
  }

 private:
  void dfs(TreeNode *root, int depth) {
    if (root == nullptr) return;
    if (depth == ans.size()) ans.emplace_back(root->val);
    dfs(root->right, depth + 1);
    dfs(root->left, depth + 1);
  }

  std::vector<int> ans;
};

}  // namespace dfs

namespace bfs {

class Solution {
 public:
  std::vector<int> rightSideView(TreeNode *root) {
    if (root == nullptr) {
      return {};
    }

    std::vector<int> ans;
    std::queue<TreeNode *> queue;
    queue.push(root);

    while (!queue.empty()) {
      int size = queue.size();
      TreeNode *tmp;
      for (int i = 0; i < size; ++i) {
        tmp = queue.front();
        queue.pop();

        if (tmp->left != nullptr) queue.push(tmp->left);
        if (tmp->right != nullptr) queue.push(tmp->right);
      }

      ans.emplace_back(tmp->val);
    }
    return ans;
  }
};

}  // namespace bfs