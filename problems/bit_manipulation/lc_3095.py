from typing import List
from math import inf
from functools import reduce


class Solution:
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        ans = inf
        n = len(nums)
        for i in range(n):
            for j in range(i, n):
                if reduce(lambda x, y: x | y, nums[i:j + 1], 0) >= k:
                    ans = min(ans, j - i + 1)
                    break
        return ans if ans != inf else -1
