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
  int pathSum(TreeNode *root, int64_t targetSum) {
    if (root == nullptr) return 0;
    // std::printf("root->val=%d, targetSum=%d, dfs(root, targetSum)=%d\n", root->val, targetSum, dfs(root, targetSum));
    return dfs(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
  }

 private:
  int dfs(TreeNode *root, int64_t targetSum) {
    int count = 0;
    if (root == nullptr) return count;

    targetSum = targetSum - root->val;

    if (targetSum == 0) {
      ++count;
    }

    count = count + dfs(root->left, targetSum);
    count = count + dfs(root->right, targetSum);
    return count;
  }
};

}  // namespace slow

namespace fast {

class Solution {
 public:
  int pathSum(TreeNode *root, int64_t targetSum) {
    prefix[0] = 1;  // empty node
    return dfs(root, targetSum, 0);
  }

 private:
  int dfs(TreeNode *root, int64_t targetSum, int64_t curr) {
    if (root == nullptr) return 0;

    int ret = 0;
    curr = curr + root->val;
    if (prefix.count(curr - targetSum) != 0) {
      ret = ret + prefix[curr - targetSum];
    }

    ++prefix[curr];  // 为什么在这里加, 想想 targetSum = 0 的情况
    ret += dfs(root->left, targetSum, curr);
    ret += dfs(root->right, targetSum, curr);
    --prefix[curr];

    return ret;
  }

  std::unordered_map<int64_t, int> prefix;
};

}  // namespace fast