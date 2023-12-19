/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <bits/stdc++.h>

struct ListNode {
    int val;
    ListNode *next{};
    explicit ListNode(int x) : val(x) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* quick, *slow;
        quick = slow = head;
        while ((quick != nullptr) && (quick->next != nullptr)) {
            quick = quick->next->next;
            slow = slow->next;
            if (quick == slow)
                return true;
        }
        return false;
    }

    ListNode *detectCycle(ListNode *head) {
        ListNode* quick, *slow;
        quick = slow = head;
        while ((quick != nullptr) && (quick->next != nullptr)) {
            quick = quick->next->next;
            slow = slow->next;
            if (slow == quick)
                break;
        }

        if ((quick == nullptr) || (quick->next == nullptr))
            return nullptr;
        
        slow = slow->next;
        while (slow != quick && slow != head) {
            slow = slow->next;
            if (slow == quick && slow != head) {
                slow = slow->next;
                head = head->next;
            }
        }
        return head;
    }
};