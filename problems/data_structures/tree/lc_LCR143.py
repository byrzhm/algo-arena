from typing import Optional


# Definition for a binary tree node.
class TreeNode:
    __slots__ = ["val", "left", "right"]

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isSubStructure(self, A: Optional[TreeNode], B: Optional[TreeNode]) -> bool:
        if A is None or B is None:
            return False

        # tree2 is contained in tree1
        def match(tree1: Optional[TreeNode], tree2: Optional[TreeNode]) -> bool:
            if tree2 is None:
                return True

            if tree1 is None:
                return False

            return (
                tree1.val == tree2.val
                and match(tree1.left, tree2.left)
                and match(tree1.right, tree2.right)
            )

        def traverse(root: Optional[TreeNode]) -> bool:
            if root is None:
                return False

            if root.val == B.val and match(root, B):
                return True

            return traverse(root.left) or traverse(root.right)

        return traverse(A)


A = TreeNode(1, TreeNode(7), TreeNode(5))
B = TreeNode(6, TreeNode(1))
ans = Solution().isSubStructure(A, B)
print(ans)
assert ans == False

A = TreeNode(1, TreeNode(7), TreeNode(5))
B = TreeNode(1, TreeNode(7))
ans = Solution().isSubStructure(A, B)
print(ans)
assert ans == True

A = TreeNode(1, TreeNode(7), TreeNode(5))
B = TreeNode(1)
ans = Solution().isSubStructure(A, B)
print(ans)
assert ans == True

A = TreeNode(1, TreeNode(7), TreeNode(5))
B = TreeNode(7)
ans = Solution().isSubStructure(A, B)
print(ans)
assert ans == True

A = TreeNode(1, TreeNode(7), TreeNode(5))
B = TreeNode(8)
ans = Solution().isSubStructure(A, B)
print(ans)
assert ans == False
