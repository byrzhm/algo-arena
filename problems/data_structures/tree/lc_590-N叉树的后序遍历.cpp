#include <__errc>
#include <utility>
#include <vector>

class Node
{
public:
  int val;
  std::vector<Node *> children;

  Node() = default;

  explicit Node(int _val)
  {
    val = _val;
  }

  Node(int _val, std::vector<Node *> _children)
  {
    val      = _val;
    children = std::move(_children);
  }
};

class Solution
{
public:
  std::vector<int> postorder(Node *root)
  {
    std::vector<int> ans;
    postorder(root, ans);
    return ans;
  }

private:
  void postorder(Node *root, std::vector<int> &ans)
  {
    if (root != nullptr) {
      for (auto * ptr : root->children) {
        postorder(ptr, ans);
      }
      ans.emplace_back(root->val);
    }
  }
};