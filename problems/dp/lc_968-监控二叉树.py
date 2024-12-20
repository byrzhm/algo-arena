from typing import Optional
from math import inf

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def minCameraCover(self, root: Optional[TreeNode]) -> int:
        def dfs(root):
            if root is None:
                return inf, 0, 0

            l_by_self, l_by_fa, l_by_son = dfs(root.left)
            r_by_self, r_by_fa, r_by_son = dfs(root.right)
            by_self = 1 + min(l_by_self, l_by_fa, l_by_son) + min(r_by_self, r_by_fa, r_by_son)
            by_fa = min(l_by_self, l_by_son) + min(r_by_self, r_by_son)
            by_son = min(l_by_self + r_by_son, r_by_self + l_by_son, l_by_self + r_by_self)
            return by_self, by_fa, by_son

        by_self, _, by_son = dfs(root)
        return min(by_self, by_son)