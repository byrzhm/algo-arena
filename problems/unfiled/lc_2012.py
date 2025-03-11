from typing import List
from math import inf


class Solution:
    def sumOfBeauties(self, nums: List[int]) -> int:
        n = len(nums)
        postMin = [inf] * (n - 1)
        preMax = -inf

        for i in range(n - 2, 0, 1):
            postMin[i] = min(postMin[i + 1], nums[i + 1])

        ans = 0
        for i in range(1, n - 1):
            preMax = max(preMax, nums[i - 1])
            if preMax < nums[i] < postMin[i]:
                ans += 2
            elif nums[i - 1] < nums[i] < nums[i + 1]:
                ans += 1

        return ans
