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
  TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
    this->preorder = &preorder;
    this->inorder = &inorder;
    int n = preorder.size();
    return dfs(0, n, 0, n);
  }

 private:
  TreeNode *dfs(int pfirst, int plast, int ifirst, int ilast) {
    if (pfirst == plast) {
      return nullptr;
    }

    std::printf("pfirst=%d, plast=%d, ifirst=%d, ilast=%d\n", pfirst, plast, ifirst, ilast);

    int root = (*preorder)[pfirst];
    int i = ifirst;
    for (; (*inorder)[i] != root; ++i)
      ;

    int leftLen = i - ifirst;

    return new TreeNode(root, dfs(pfirst + 1, pfirst + 1 + leftLen, ifirst, i),
                        dfs(pfirst + 1 + leftLen, plast, i + 1, ilast));
  }

  std::vector<int> *preorder;
  std::vector<int> *inorder;
};

}  // namespace sol1

namespace sol2 {

// class Solution {
//  public:
//   TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
//     this->preorder = &preorder;
//     this->inorder = &inorder;

//     for (int i = 0; i < inorder.size(); ++i) map[inorder[i]] = i;

//     int n = preorder.size();
//     return dfs(0, n, 0, n);
//   }

//  private:
//   TreeNode *dfs(int pfirst, int plast, int ifirst, int ilast) {
//     if (pfirst == plast) return nullptr;

//     int root = (*preorder)[pfirst];
//     int i = map[root];

//     int leftLen = i - ifirst;

//     return new TreeNode(root, dfs(pfirst + 1, pfirst + 1 + leftLen, ifirst, i),
//                         dfs(pfirst + 1 + leftLen, plast, i + 1, ilast));
//   }

//   std::unordered_map<int, int> map;
//   std::vector<int> *preorder;
//   std::vector<int> *inorder;
// };

class Solution {
 public:
  TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
    this->preorder = &preorder;
    // this->inorder = &inorder;

    for (int i = 0; i < inorder.size(); ++i) map[inorder[i]] = i;

    int n = preorder.size();
    return dfs(0, /* n, */ 0, n);
  }

 private:
  TreeNode *dfs(int pfirst, /* int plast, */ int ifirst, int ilast) {
    if (ifirst == ilast) return nullptr;

    int root = (*preorder)[pfirst];
    int i = map[root];

    int leftLen = i - ifirst;

    return new TreeNode(root, dfs(pfirst + 1 /*, pfirst + 1 + leftLen */, ifirst, i),
                        dfs(pfirst + 1 + leftLen /*, plast */, i + 1, ilast));
  }

  std::unordered_map<int, int> map;
  std::vector<int> *preorder;
  // std::vector<int> *inorder;
};

}  // namespace sol2

void inorder(TreeNode *root) {
  if (root != nullptr) {
    inorder(root->left);
    std::cout << root->val << '\n';
    inorder(root->right);
  }
}

int main() {
  std::vector<int> preorder = {3, 9, 20, 15, 7};
  std::vector<int> inorder = {9, 3, 15, 20, 7};
  TreeNode *root = sol1::Solution().buildTree(preorder, inorder);
  ::inorder(root);
}