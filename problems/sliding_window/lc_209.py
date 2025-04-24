from typing import List


class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        n = len(nums)
        ans = n + 1
        s = left = 0
        for right, x in enumerate(nums):
            s += x
            while s >= target:
                ans = min(ans, right - left + 1)
                s -= nums[left]
                left += 1
        return ans if ans <= n else 0


class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        n = len(nums)
        ans = n + 1
        s = left = 0
        for right, x in enumerate(nums):
            s += x
            while s - nums[left] >= target:
                s -= nums[left]
                left += 1
            if s >= target:
                ans = min(ans, right - left + 1)
        return ans if ans <= n else 0
