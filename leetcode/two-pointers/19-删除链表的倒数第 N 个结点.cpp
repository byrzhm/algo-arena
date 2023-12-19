#include <bits/stdc++.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* slow, * fast, * tmp;
        slow = fast = head;
        n++;

        while ((fast != nullptr) && (n != 0)) {
            fast = fast->next;
            n--;
        }

        if ((fast == nullptr) && n == 1) {
            tmp = head;
            head = head->next;
        } else {
            while (fast != nullptr) {
                fast = fast->next;
                slow = slow->next;
            }
            tmp  = slow->next;
            slow->next = tmp->next;
        }

        delete tmp;
        return head;
    }
};