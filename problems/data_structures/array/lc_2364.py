from typing import List
from collections import defaultdict


class Solution:
    def countBadPairs(self, nums: List[int]) -> int:
        ans = 0
        tbl = defaultdict(int)
        for i, x in enumerate(nums):
            ans += i - tbl[x - i]
            tbl[x - i] += 1
        return ans
