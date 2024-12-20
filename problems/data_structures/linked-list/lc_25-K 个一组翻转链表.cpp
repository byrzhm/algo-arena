#include <iostream>
#include <memory>

struct ListNode
{
  int val;
  ListNode *next;
  ListNode()
    : val(0)
    , next(nullptr)
  {}
  explicit ListNode(int x)
    : val(x)
    , next(nullptr)
  {}
  ListNode(int x, ListNode *next)
    : val(x)
    , next(next)
  {}
};

class Solution
{
public:
  ListNode *reverseKGroup(ListNode *head, int k)
  {
    std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>(0, head);
    ListNode *prev                  = dummy.get();
    ListNode *curr                  = prev->next;
    int count                       = 0;

    while (curr != nullptr) {
      ListNode *save = curr;
      ListNode *nextKGroup = curr;
      for (count = 0; count < k && nextKGroup != nullptr; ++count) {
        nextKGroup = nextKGroup->next;
      }

      if (count < k)
        break;

      prev->next = nextKGroup;
      while (curr != nextKGroup) {
        ListNode *temp = curr->next;
        curr->next     = prev->next;
        prev->next     = curr;
        curr           = temp;
      }

      prev = save;
      curr = nextKGroup;
    }

    return dummy->next;
  }
};