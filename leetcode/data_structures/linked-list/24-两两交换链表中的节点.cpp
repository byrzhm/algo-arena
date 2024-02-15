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
  ListNode *swapPairs(ListNode *head)
  {
    std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>(0, head);
    ListNode *prev                  = dummy.get();
    ListNode *curr                  = prev->next;

    while (curr != nullptr && curr->next != nullptr) {
      ListNode *temp = curr->next;
      prev->next     = temp;
      curr->next     = temp->next;
      temp->next     = curr;
      prev           = curr;
      curr           = curr->next;
    }

    return dummy->next;
  }
};
