#include <iostream>

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
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
  {
    auto head  = new ListNode();
    auto *prev = head;
    auto *curr = prev->next;
    int carry  = 0;

    while (l1 != nullptr || l2 != nullptr) {
      int n1     = l1 != nullptr ? l1->val : 0;
      int n2     = l2 != nullptr ? l2->val : 0;
      int sum    = n1 + n2 + carry;
      int remain = sum % 10;
      carry      = sum / 10;

      curr       = new ListNode(remain);

      if (l1 != nullptr)
        l1 = l1->next;
      if (l2 != nullptr)
        l2 = l2->next;

      prev->next = curr;
      prev = prev->next;
      curr = curr->next;
    }

    if (carry > 0) {
      curr       = new ListNode(carry);
      prev->next = curr;
    }

    curr = head;
    head = head->next;
    delete curr;

    return head;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  return 0;
}