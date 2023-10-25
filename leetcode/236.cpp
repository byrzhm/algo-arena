// lowest common ancestor of a binary tree
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    unordered_map<int, TreeNode*> fa;
    unordered_map<int, bool> vis;
public:
    void dfs(TreeNode* root) {
        if (root->left) {
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right) {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        fa[root->val] = NULL;
        dfs(root);

        while (p != NULL) {
            vis[p->val] = true;
            p = fa[p->val];
        }

        while (q != NULL) {
            if (vis[q->val]) return q;
            q = fa[q->val];
        }
        return NULL;
    }
};