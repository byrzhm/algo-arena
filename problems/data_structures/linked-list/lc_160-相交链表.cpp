#include <bits/stdc++.h>

struct ListNode
{
  int val;
  ListNode *next{};
  explicit ListNode(int x)
    : val(x)
  {}
};

namespace hashtable {

class Solution
{
public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
  {
    std::unordered_set<ListNode *> set;
    while (headA != nullptr) {
      set.insert(headA);
      headA = headA->next;
    }

    while (headB != nullptr) {
      if (set.count(headB) > 0) {
        return headB;
      }
      headB = headB->next;
    }
    return nullptr;
  }
};

}  // namespace hashtable

namespace two_pointer {

class Solution
{
public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
  {
    if (headA == nullptr || headB == nullptr)
      return nullptr;

    ListNode *pA = headA, *pB = headB;
    while (pA != pB) {
      pA = pA == nullptr ? headB : pA->next;
      pB = pB == nullptr ? headA : pB->next;
    }
    return pA;
  }
};


}  // namespace two_pointer
