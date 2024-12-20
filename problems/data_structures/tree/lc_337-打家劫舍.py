from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def rob(self, root: Optional[TreeNode]) -> int:
        def dfs(root):
            if root == None:
                return (0, 0)

            l, ln = dfs(root.left)
            r, rn = dfs(root.right)

            return (root.val + ln + rn, max(l, ln) + max(r, rn))

        return max(dfs(root))
        