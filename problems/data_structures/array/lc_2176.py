from typing import List
from collections import defaultdict


class Solution:
    def countPairs(self, nums: List[int], k: int) -> int:
        tbl = defaultdict(list)
        ans = 0
        for i, x in enumerate(nums):
            for j in tbl[x]:
                if i * j % k == 0:
                    ans += 1
            tbl[x].append(i)
        return ans
