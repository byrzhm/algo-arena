#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <ostream>
#include <queue>
#include <utility>
#include <vector>

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

// 为什么 make_heap 这么慢 😡
namespace make_heap {

class Solution
{
public:
  ListNode *mergeKLists(std::vector<ListNode *> &lists)
  {
    std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>();
    ListNode *curr                  = dummy.get();

    int size = lists.size();

    for (int i = 0, j = lists.size() - 1; i <= j;) {
      if (lists[i] == nullptr) {
        --size;
        std::swap(lists[i], lists[j--]);
      } else {
        ++i;
      }
    }

    auto listNodeComparator = [](ListNode *n1, ListNode *n2) {
      return n1->val > n2->val;
    };

    while (size > 0) {
      std::make_heap(lists.begin(), lists.begin() + size, listNodeComparator);
      std::pop_heap(lists.begin(), lists.begin() + size);
      auto node = lists[size - 1];
      if (node->next != nullptr) {
        lists[size - 1] = node->next;
      } else {
        --size;
      }

      node->next = nullptr;
      curr->next = node;
      curr       = curr->next;
    }

    return dummy->next;
  }
};

}  // namespace make_heap

namespace pq {

class Solution
{
public:
  ListNode *mergeKLists(std::vector<ListNode *> &lists)
  {
    std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>();
    ListNode *curr                  = dummy.get();
    auto listNodeComparator         = [](ListNode *n1, ListNode *n2) {
      return n1->val > n2->val;
    };

    std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(listNodeComparator)> pq(listNodeComparator);

    for (auto node : lists) {
      if (node != nullptr) {
        pq.emplace(node);
      }
    }

    while (!pq.empty()) {
      auto node = pq.top();
      pq.pop();
      if (node->next != nullptr) {
        pq.push(node->next);
      }

      node->next = nullptr;
      curr->next = node;
      curr       = node;
    }

    return dummy->next;
  }
};

}  // namespace pq

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

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<ListNode *> lists{
      createList({1, 4, 5}),
      createList({1, 3, 4}),
      createList({2, 6})
  };

  ListNode *ans = pq::Solution().mergeKLists(lists);
  printList(ans);
  destroyList(ans);

  return 0;
}