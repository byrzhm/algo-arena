from typing import List
from collections import defaultdict


class Solution:
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        tbl = [0] * 100
        ans = 0
        for x, y in dominoes:
            if x > y:
                t = y * 10 + x
            else:
                t = x * 10 + y
            ans += tbl[t]
            tbl[t] += 1
        return ans
