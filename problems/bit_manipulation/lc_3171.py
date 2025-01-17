"""
See: 
https://leetcode.cn/problems/find-subarray-with-bitwise-or-closest-to-k/solutions/2798206/li-yong-and-de-xing-zhi-pythonjavacgo-by-gg4d/

把二进制数看成集合，两个数的 OR 就是两个集合的并集.
对于两个二进制数 a 和 b，如果 (a ∣ b) == a，那么 b 对应的集合是 a 对应的集合的子集.
"""

from typing import List
from math import inf


# 暴力算法，会超时
class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        ans = inf
        for i, x in enumerate(nums):
            ans = min(ans, abs(x - k))  # 单个元素也算子数组
            for j in range(i - 1, -1, -1):
                nums[j] |= x  # 现在 nums[j] = 原数组 nums[j] 到 nums[i] 的 OR
                ans = min(ans, abs(nums[j] - k))
        return ans


class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        ans = inf
        for i, x in enumerate(nums):
            ans = min(ans, abs(x - k))
            j = i - 1
            while j >= 0 and nums[j] | x != nums[j]:
                nums[j] |= x
                ans = min(ans, abs(nums[j] - k))
                j -= 1
        return ans
