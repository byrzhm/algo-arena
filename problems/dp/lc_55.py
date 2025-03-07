from typing import List
from functools import cache


class Solution:
    def canJump(self, nums: List[int]) -> bool:
        n = len(nums)

        @cache
        def dfs(i: int) -> bool:
            if i == 0:
                return True

            for j in range(i - 1, -1, -1):
                if dfs(j) and j + nums[j] >= i:
                    return True
            return False

        return dfs(n - 1)


class Solution:
    def canJump(self, nums: List[int]) -> bool:
        n = len(nums)
        rightmost = 0
        for i, x in enumerate(nums):
            if i <= rightmost:
                rightmost = max(rightmost, i + x)
                if rightmost >= n - 1:
                    return True
        return False