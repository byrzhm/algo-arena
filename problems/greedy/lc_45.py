from typing import List
from math import inf
from functools import cache


"""
https://leetcode.cn/problems/jump-game-ii/?envType=daily-question&envId=2025-01-27
"""


class Solution:
    def jump(self, nums: List[int]) -> int:
        n = len(nums)

        @cache
        def dfs(i: int) -> int:
            if i == 0:
                return 0
            res = inf
            for j in range(i):
                if nums[j] + j >= i:
                    res = min(res, dfs(j) + 1)
            return res

        return dfs(n - 1)


class Solution:
    def jump(self, nums: List[int]) -> int:
        ans = 0
        curr_right = 0
        next_right = 0
        n = len(nums)
        for i in range(n - 1):  # why n - 1 ?
            next_right = max(next_right, i + nums[i])
            if i == curr_right:
                curr_right = next_right
                ans += 1
        return ans
