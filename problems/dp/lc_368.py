from typing import List
from functools import cache


"""
class Solution:
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        n = len(nums)
        nums.sort()
        dp = [[] for _ in range(n + 1)]
        max_loc, max_len = 0, 0

        for i in range(1, n + 1):
            t = nums[i - 1]
            for j in range(len(dp[i - 1]) - 1, -1, -1):
                if t % dp[i - 1][j] == 0:
                    dp[i] = dp[i - 1][: j + 1]
                    break
            dp[i].append(t)
            if len(dp[i]) > max_len:
                max_len = len(dp[i])
                max_loc = i

        return dp[max_loc]
"""


class Solution:
    def largestDivisibleSubset(self, nums: List[int]) -> List[int]:
        nums.sort()
        n = len(nums)
        from_ = [-1] * n

        @cache  # 缓存装饰器，避免重复计算 dfs（一行代码实现记忆化）
        def dfs(i: int) -> int:
            res = 0
            for j in range(i):
                if nums[i] % nums[j]:
                    continue
                f = dfs(j)
                if f > res:
                    res = f
                    from_[i] = j  # 记录最佳转移来源
            return res + 1  # 加上 nums[i] 自己

        max_f = max_i = 0
        for i in range(n):
            f = dfs(i)
            if f > max_f:
                max_f = f
                max_i = i  # 最长合法子序列的最后一个数的下标

        path = []
        i = max_i
        while i >= 0:
            path.append(nums[i])
            i = from_[i]
        return path  # 不需要 reverse，任意顺序返回均可


# nums = [1, 2, 3]
# print(Solution().largestDivisibleSubset(nums))

nums = [2, 3, 4, 8]
print(Solution().largestDivisibleSubset(nums))
