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
  int maxPathSum(TreeNode *root) {  // 根节点可以选也可以不选
                                    // 确保第一次调用dfs时, 传入参数非空
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return root->val;
    if (root->left == nullptr) return std::max(dfs(root).second, maxPathSum(root->right));
    if (root->right == nullptr) return std::max(dfs(root).second, maxPathSum(root->left));
    return std::max(dfs(root).second, std::max(maxPathSum(root->left), maxPathSum(root->right)));
  }

 private:
  // 根节点必须选择, 第一个值返回作为中间节点的情况, 第二个值返回作为根节点的情况
  std::pair<int, int> dfs(TreeNode *root) {
    if (root == nullptr) return {0, 0};

    auto [la, lb] = dfs(root->left);
    auto [ra, rb] = dfs(root->right);
    int a = std::max(0, std::max(la, ra));
    int b = std::max(a, la + ra);
    return {a + root->val, b + root->val};
  }
};

}  // namespace slow

namespace fast {

class Solution {
 public:
  int maxPathSum(TreeNode *root) {
    dfs(root);
    return maxSum;
  }

 private:
  int dfs(TreeNode *root) {  // root 必须包含在局部 maxSum 中
    if (root == nullptr) return 0;
    int l = dfs(root->left);
    int r = dfs(root->right);

    int t = std::max(0, std::max(l, r));                        // 不选, 只选左边, 或者只选右边
    maxSum = std::max(std::max(t, l + r) + root->val, maxSum);  // maxSum 还要考虑两边都选的情况

    return t + root->val;  // 根据节点序列的定义, 返回给上层的, 不应包含两边都选, root 必须包含在内
  }

  int maxSum = std::numeric_limits<int>::min();
};

}  // namespace fast