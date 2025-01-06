from typing import List
from functools import cache


class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)

        # dfs(i) 表示考虑前 i 间房子所能获得的最大收益
        @cache
        def dfs(i):
            if i == 0:
                return 0
            if i == 1:
                return nums[0]
            # dfs(i - 1) 不偷第 i 间房子, 只在前 i - 1 个房子里偷
            # dfs(i - 2) 不偷第 i - 1 间房子, 偷第 i 间房子和前 i - 2 间房子
            return max(dfs(i - 1), dfs(i - 2) + nums[i - 1])

        return dfs(n)


class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        p, q, r = 0, 0, 0
        for i in range(1, n + 1):
            p = q
            q = r
            r = max(q, p + nums[i - 1])
        return r
