from typing import List


class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        for i in range(n):
            for j in range(i + 1, n):
                for k in range(j + 1, n):
                    ans = max(ans, (nums[i] - nums[j]) * nums[k])
        return ans


class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        premax = maxdif = ans = 0
        for x in nums:
            ans = max(ans, maxdif * x)
            maxdif = max(maxdif, premax - x)
            premax = max(premax, x)
        return ans
