from typing import List


class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        minDp = 0
        maxDp = 0
        ans = 0
        n = len(nums)
        for i in range(1, n + 1):
            minDp = min(minDp + nums[i - 1], nums[i - 1])
            maxDp = max(maxDp + nums[i - 1], nums[i - 1])
            ans = max(ans, abs(minDp), maxDp)
        return ans
