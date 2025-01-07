from typing import List
from functools import cache
from math import inf


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)

        @cache
        def dfs(i):
            if i == 0:
                return -inf
            return max(dfs(i - 1) + nums[i - 1], nums[i - 1])

        return max(dfs(i) for i in range(n + 1))


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        ans = -inf
        dp = -inf
        for i in range(1, n + 1):
            dp = max(dp + nums[i - 1], nums[i - 1])
            ans = max(ans, dp)
        return ans
