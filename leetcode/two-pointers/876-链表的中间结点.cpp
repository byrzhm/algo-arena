struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *quick, *slow;
        quick = slow = head;
        while ((quick != nullptr) && (quick->next != nullptr)) {
            quick = quick->next->next;
            slow = slow->next;
        }
        return slow;
    }
};