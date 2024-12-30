from typing import Optional


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# O(mn)
class Solution:
    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        is_sub_path = False

        def dfs(head: Optional[ListNode], root: Optional[TreeNode], prev_match: bool):
            nonlocal is_sub_path
            if is_sub_path:
                return

            if prev_match and head is None:
                is_sub_path = True
                return

            if head is not None and root is not None and head.val == root.val:
                dfs(head.next, root.left, True)
                dfs(head.next, root.right, True)

            if not prev_match:
                if head and root.left:
                    dfs(head, root.left, False)
                if head and root.right:
                    dfs(head, root.right, False)

        dfs(head, root, False)
        return is_sub_path
