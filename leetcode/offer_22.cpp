#include <bits/stdc++.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        int cnt = 0;
        ListNode *slow, *fast;
        slow = fast = head;
        while (fast) {
            if (cnt < k) {
                cnt++;
                fast = fast->next;
            } else {
                fast = fast->next;
                slow = slow->next;
            }
        }
        return slow;
    }
};