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
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* quick, *slow;
        quick = slow = head;
        while (quick && quick->next) {
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
        while (quick && quick->next) {
            quick = quick->next->next;
            slow = slow->next;
            if (slow == quick)
                break;
        }

        if (!quick || !quick->next)
            return NULL;
        else {
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
    }
};