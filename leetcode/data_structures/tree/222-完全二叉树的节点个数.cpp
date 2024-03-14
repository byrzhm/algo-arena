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
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;

        int level = 0;
        TreeNode *p = root;
        while (p->left != nullptr) {
            ++level;
            p = p->left;
        }

        int l = 1 << level;
        int r = (1 << (level + 1)) - 1;
        
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (exists(root, level, mid)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }
private:
    bool exists(TreeNode *root, int level, int k) {
        int bits = 1 << (level - 1);
        TreeNode *node = root;
        while (node != nullptr && bits > 0) {
            if ((bits & k) == 0) {
                node = node->left;
            } else {
                node = node->right;
            }
            bits >>= 1;
        }
        return node != nullptr;
    }
};