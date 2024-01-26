#include <bits/stdc++.h>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace sol1 {

class Solution {
 public:
  bool isValidBST(TreeNode *root) {
    if (root == nullptr) {
      return true;
    }

    dfs(root);
    return valid;
  }

 private:
  // 左边返回最大的数, 右边返回最小的数
  std::pair<int, int> dfs(TreeNode *root) {
    if (!valid) return {};

    if (root->left == nullptr && root->right == nullptr) {
      // std::cout << ++timestamp << ": " << (root->val) << std::endl;
      return {root->val, root->val};
    }

    if (root->left == nullptr) {
      auto [rmin, rmax] = dfs(root->right);
      if (root->val >= rmin) {
        valid = false;
        return {};
      }
      // std::cout << ++timestamp << ": " << root->val << ", " << rmax << std::endl;
      return {root->val, rmax};
    }

    if (root->right == nullptr) {
      auto [lmin, lmax] = dfs(root->left);
      if (root->val <= lmax) {
        valid = false;
        return {};
      }
      // std::cout << ++timestamp << ": " << lmin << ", " << root->val << std::endl;
      return {lmin, root->val};
    }

    auto [lmin, lmax] = dfs(root->left);
    auto [rmin, rmax] = dfs(root->right);

    if (root->val >= rmin || root->val <= lmax) {
      valid = false;
      return {};
    }

    // std::cout << ++timestamp << ": " << lmax << ": " << rmax << std::endl;
    return {lmin, rmax};
  }

  bool valid = true;
  // int timestamp = 0;
};

}  // namespace sol1

namespace sol2 {

class Solution {
 public:
  bool isValidBST(TreeNode *root) {
    return dfs(root, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
  }

  bool dfs(TreeNode *root, int64_t lb, int64_t ub) {
    if (root == nullptr) {
      return true;
    }

    if (root->val <= lb || root->val >= ub) {
      return false;
    }

    return dfs(root->left, lb, root->val) && dfs(root->right, root->val, ub);
  }
};

}  // namespace sol2

namespace sol3 {

class Solution {
 public:
  bool isValidBST(TreeNode *root) {
    std::stack<TreeNode *> stack;
    int64_t prev = std::numeric_limits<int64_t>::min();

    while (!stack.empty() || root != nullptr) {
      while (root != nullptr) {  // 一直向左走
        stack.push(root);
        root = root->left;
      }

      root = stack.top();  // 到达最左边的节点
      stack.pop();

      // 中序遍历
      if (root->val <= prev) {
        return false;
      }

      prev = root->val;
      root = root->right;  // 转向右子树
    }
    return true;
  }
};

}  // namespace sol3