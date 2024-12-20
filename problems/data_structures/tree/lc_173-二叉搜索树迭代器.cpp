#include <queue>
#include <stack>

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode()
    : val(0)
    , left(nullptr)
    , right(nullptr)
  {}
  explicit TreeNode(int x)
    : val(x)
    , left(nullptr)
    , right(nullptr)
  {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
    : val(x)
    , left(left)
    , right(right)
  {}
};

namespace stack {

class BSTIterator
{
public:
  explicit BSTIterator(TreeNode *root)
  {
    while (root != nullptr) {
      stk.push(root);
      root = root->left;
    }
  }

  int next()
  {
    TreeNode *t = stk.top();
    stk.pop();
    int val = t->val;
    if (t->right != nullptr) {
      t = t->right;
      while (t != nullptr) {
        stk.push(t);
        t = t->left;
      }
    }
    return val;
  }

  bool hasNext()
  {
    return !stk.empty();
  }

private:
  std::stack<TreeNode *> stk;
};

}  // namespace stack

namespace flatten {

class BSTIterator
{
public:
  explicit BSTIterator(TreeNode *root)
  {
    inorder(root);
  }

  void inorder(TreeNode *root)
  {
    if (root != nullptr) {
      inorder(root->left);
      q.emplace(root);
      inorder(root->right);
    }
  }

  int next()
  {
    int val{q.front()->val};
    q.pop();
    return val;
  }

  bool hasNext()
  {
    return !q.empty();
  }

private:
  std::queue<TreeNode *> q;
};

}  // namespace flatten

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */