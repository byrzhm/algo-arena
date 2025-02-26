class ListNode:
    __slots__ = ["val", "next"]

    def __init__(self, val=0, next=None):
        self.val: int = val
        self.next: ListNode = next

    def __repr__(self) -> str:
        return f"ListNode{{val: {self.val}, next: {self.next}}}"


# insertion sort
class Solution:
    def sortList(self, head: ListNode) -> ListNode:
        dummy_head = ListNode()
        while head is not None:
            node = head
            head = head.next

            # invariant: ptr.val < node.val <= ptr.next.val
            ptr = dummy_head
            while ptr.next is not None and ptr.next.val < node.val:
                ptr = ptr.next

            node.next = ptr.next
            ptr.next = node

        return dummy_head.next


# merge sort
class Solution:
    def sortList(self, head: ListNode) -> ListNode:
        return self.mergeSort(head)

    def mergeSort(self, head: ListNode) -> ListNode:
        if head is None or head.next is None:
            return head

        slow, fast = head, head
        while fast is not None and fast.next is not None and fast.next.next is not None:
            slow = slow.next
            fast = fast.next.next
        head2 = slow.next
        slow.next = None
        head = self.mergeSort(head)
        head2 = self.mergeSort(head2)
        return self.merge(head, head2)

    def merge(self, head1: ListNode, head2: ListNode) -> ListNode:
        dummy = ListNode()
        curr = dummy
        while head1 is not None and head2 is not None:
            if head1.val < head2.val:
                curr.next = head1
                head1 = head1.next
                curr = curr.next
            else:
                curr.next = head2
                head2 = head2.next
                curr = curr.next
        curr.next = head1 if head1 is not None else head2
        return dummy.next


dummy = ListNode()
nums = [4, 2, 1, 3]
for num in reversed(nums):
    node = ListNode(val=num, next=dummy.next)
    dummy.next = node

print(dummy.next)

dummy.next = Solution().sortList(dummy.next)

print(dummy.next)
