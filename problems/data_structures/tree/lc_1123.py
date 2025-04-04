from typing import Optional
from collections import deque


# Definition for a binary tree node.
class TreeNode:
    __slots__ = ["val", "left", "right"]

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        ans = None
        max_depth = -1

        def dfs(root: Optional[TreeNode], depth: int) -> int:
            nonlocal ans, max_depth
            if root is None:
                return depth - 1

            if root.left is None and root.right is None:
                if depth > max_depth:
                    max_depth = depth
                    ans = root
                return depth

            left_depth = dfs(root.left, depth + 1)
            right_depth = dfs(root.right, depth + 1)
            if left_depth == right_depth == max_depth:
                ans = root

            return max(left_depth, right_depth)

        dfs(root, 0)
        return ans


class Solution:
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        ans = None
        max_depth = -1

        def dfs(root: Optional[TreeNode], depth: int) -> int:
            nonlocal ans, max_depth
            if root is None:
                max_depth = max(max_depth, depth)
                return depth

            left_depth = dfs(root.left, depth + 1)
            right_depth = dfs(root.right, depth + 1)
            if left_depth == right_depth == max_depth:
                ans = root

            return max(left_depth, right_depth)

        dfs(root, 0)
        return ans
