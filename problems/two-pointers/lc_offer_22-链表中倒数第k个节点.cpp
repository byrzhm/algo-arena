#include <bits/stdc++.h>

struct ListNode {
    int val;
    ListNode *next{};
    explicit ListNode(int x) : val(x) {}
};

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        int cnt = 0;
        ListNode *slow, *fast;
        slow = fast = head;
        while (fast != nullptr) {
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