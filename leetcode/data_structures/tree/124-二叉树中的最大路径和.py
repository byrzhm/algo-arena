from typing import Optional
from math import inf

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        ans = -inf
        def dfs(root):
            if root == None:
                return -inf

            left = max(dfs(root.left), 0) + root.val
            right = max(dfs(root.right), 0) + root.val
            
            nonlocal ans
            ans = max(ans, left + right - root.val)
            return max(left, right)

        dfs(root)
        return ans
        