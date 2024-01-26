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
  TreeNode *sortedArrayToBST(std::vector<int> &nums) {
    if (nums.empty()) {
      return nullptr;
    }

    return createTreeNode(nums, 0, nums.size());
  }

 private:
  TreeNode *createTreeNode(std::vector<int> &nums, int first, int last) {
    if (first == last) return nullptr;

    int mid = (first + last) >> 1;

    return new TreeNode{nums[mid], createTreeNode(nums, first, mid), createTreeNode(nums, mid + 1, last)};
  }
};

void inorder(TreeNode *root) {
  if (root != nullptr) {
    inorder(root->left);
    std::cout << root->val << '\n';
    inorder(root->right);
  }
}

int main() {
  std::vector<int> nums{1, 2, 3, 4, 5};
  TreeNode *root = Solution().sortedArrayToBST(nums);
  inorder(root);
}