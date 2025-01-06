from typing import List
from collections import Counter
from functools import cache


class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        maxVal = max(nums)
        total = [0] * (maxVal + 1)
        for x in nums:
            total[x] += x

        @cache
        def dfs(i):
            if i == 0:
                return 0
            if i == 1:
                return total[0]
            return max(dfs(i - 1), dfs(i - 2) + total[i - 1])

        return dfs(maxVal + 1)


nums = [3, 4, 2]
assert Solution().deleteAndEarn(nums) == 6


class Solution:
    def deleteAndEarn(self, nums: List[int]) -> int:
        maxVal = max(nums)
        total = [0] * (maxVal + 1)
        for x in nums:
            total[x] += x

        def rob(nums: List[int]) -> int:
            n = len(nums)
            p, q, r = 0, 0, 0
            for i in range(1, n + 1):
                p = q
                q = r
                r = max(q, p + nums[i - 1])
            return r

        return rob(total)
