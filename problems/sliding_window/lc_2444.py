from typing import List


class Solution:
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        ans = 0
        min_i = max_i = i0 = -1
        for i, x in enumerate(nums):
            if x == minK:
                min_i = i  # 最近的 minK 位置
            if x == maxK:
                max_i = i  # 最近的 maxK 位置
            if not minK <= x <= maxK:
                i0 = i  # 子数组不能包含 nums[i0]
            ans += max(min(min_i, max_i) - i0, 0)
        return ans


class Solution:
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        ans = 0
        min_i = max_i = i0 = -1
        for i, x in enumerate(nums):
            if x == minK:
                min_i = i
            if x == maxK:
                max_i = i
            if not minK <= x <= maxK:
                i0 = i
            j = min_i if min_i < max_i else max_i
            if j > i0:
                ans += j - i0
        return ans
