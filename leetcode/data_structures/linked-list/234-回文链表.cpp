#include <deque>

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
  bool isPalindrome(ListNode *head)
  {
    std::deque<int> order;
    std::deque<int> reverse;

    while (head != nullptr) {
      order.push_back(head->val);
      reverse.push_front(head->val);
      head = head->next;
    }

    while (!order.empty()) {
      if (order.front() != reverse.front()) {
        return false;
      }
      order.pop_front();
      reverse.pop_front();
    }
    return true;
  }
};