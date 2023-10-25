#include <bits/stdc++.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* slow, * fast, * tmp;
        slow = fast = head;
        n++;

        while (fast && n) {
            fast = fast->next;
            n--;
        }

        if (!fast && n == 1) {
            tmp = head;
            head = head->next;
        } else {
            while (fast) {
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