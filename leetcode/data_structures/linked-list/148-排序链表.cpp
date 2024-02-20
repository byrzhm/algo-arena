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

ListNode *createList(const std::initializer_list<int> &init_list)
{
  std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>();
  ListNode *curr                  = dummy.get();
  for (auto item : init_list) {
    curr->next = new ListNode(item);
    curr       = curr->next;
  }
  return dummy->next;
}

void destroyList(ListNode *head)
{
  while (head != nullptr) {
    ListNode *tmp = head;
    head          = head->next;
    delete tmp;
  }
}

void printList(ListNode *head)
{
  if (head != nullptr) {
    std::cout << head->val << "->";
    printList(head->next);
  } else {
    std::cout << "null\n";
  }
}

class Solution
{
public:
  ListNode *sortList(ListNode *head)
  {
    return mergeSort(head, nullptr);
  }

private:
  // return null terminated List
  ListNode *mergeSort(ListNode *head, ListNode *tail)
  {
    if (head == tail)
      return nullptr;

    if (head->next == tail) {
      head->next = nullptr;
      return head;
    }

    ListNode *quick = head->next->next;
    ListNode *slow  = head->next;

    // quick == nullptr -> length % 2 == 0
    // quick->next == nullptr -> length % 2 == 1
    while (quick != tail && quick->next != tail) {
      quick = quick->next->next;
      slow  = slow->next;
    }

    ListNode *half = slow;
    head           = mergeSort(head, half);
    half           = mergeSort(half, tail);
    return merge(head, half);
  }

  ListNode *merge(ListNode *head1, ListNode *head2)
  {
    auto dummy = std::make_unique<ListNode>();
    auto tail  = dummy.get();
    ListNode *tmp;

    while (head1 != nullptr && head2 != nullptr) {
      if (head1->val < head2->val) {
        tmp   = head1;
        head1 = head1->next;
      } else {
        tmp   = head2;
        head2 = head2->next;
      }
      tmp->next  = nullptr;
      tail->next = tmp;
      tail       = tmp;
    }

    while (head1 != nullptr) {
      tmp        = head1;
      head1      = head1->next;
      tmp->next  = nullptr;
      tail->next = tmp;
      tail       = tmp;
    }

    while (head2 != nullptr) {
      tmp        = head2;
      head2      = head2->next;
      tmp->next  = nullptr;
      tail->next = tmp;
      tail       = tmp;
    }

    return dummy->next;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto list = createList({5, 2, 3, 1, 4});
  list      = Solution().sortList(list);
  printList(list);
  destroyList(list);

  return 0;
}