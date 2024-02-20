#include <unordered_map>

class Node
{
public:
  int val;
  Node *next;
  Node *random;

  explicit Node(int _val)
  {
    val    = _val;
    next   = nullptr;
    random = nullptr;
  }
};

class Solution
{
public:
  Node *copyRandomList(Node *head)
  {
    std::unordered_map<Node *, Node *> nodeMap;

    Node *curr = head;
    while (curr != nullptr) {
      nodeMap.emplace(curr, new Node(curr->val));
      curr = curr->next;
    }

    curr = head;
    while (curr != nullptr) {
      nodeMap[curr]->random = nodeMap[curr->random];
      nodeMap[curr]->next = nodeMap[curr->next];
      curr = curr->next;
    }

    return nodeMap[head];
  }
};
