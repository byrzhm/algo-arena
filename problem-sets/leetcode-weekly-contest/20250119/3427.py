from typing import List
from itertools import accumulate


class Solution:
    def subarraySum(self, nums: List[int]) -> int:
        ans = 0
        prefixSum = list(accumulate(nums, initial=0))
        for i, x in enumerate(nums):
            start = max(0, i - x)
            # ans += sum(nums[start : i + 1])
            ans += prefixSum[i + 1] - prefixSum[start]
        return ans
