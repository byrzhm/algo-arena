from typing import List
from math import inf


class Solution:
    def lengthOfLongestSubsequence(self, nums: List[int], target: int) -> int:
        # f[i][j] 选取前 i 个数字，和为 j 的子序列最大长度
        # f[i][j] <- max(f[i-1][j], f[i-1][j-nums[i]] + 1) 不要或要
        n = len(nums)
        f = [[-inf] * (target + 1) for _ in range(n + 1)]
        f[0][0] = 0
        for i in range(1, n + 1):
            for j in range(0, target + 1):
                f[i][j] = f[i - 1][j]
                if j >= nums[i - 1]:
                    f[i][j] = max(f[i][j], f[i - 1][j - nums[i - 1]] + 1)
        return f[n][target]


class Solution:
    def lengthOfLongestSubsequence(self, nums: List[int], target: int) -> int:
        n = len(nums)
        f = [0] + [-inf] * target
        for x in nums:
            for j in range(target, x - 1, -1):
                if f[j] < f[j - x] + 1:
                    f[j] = f[j - x] + 1
        return f[target] if f[target] > 0 else -1
