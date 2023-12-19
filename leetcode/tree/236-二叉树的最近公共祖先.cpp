// lowest common ancestor of a binary tree
#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode *left{};
    TreeNode *right{};
    explicit TreeNode(int x) : val(x) {}
};

class Solution {
    std::unordered_map<int, TreeNode *> fa;
    std::unordered_map<int, bool> vis;

   public:
    void dfs(TreeNode* root) {
        if (root->left != nullptr) {
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != nullptr) {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        fa[root->val] = nullptr;
        dfs(root);

        while (p != nullptr) {
            vis[p->val] = true;
            p = fa[p->val];
        }

        while (q != nullptr) {
            if (vis[q->val]) return q;
            q = fa[q->val];
        }
        return nullptr;
    }
};