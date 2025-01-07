from typing import List
from math import inf


class Solution:
    def maximumCostSubstring(self, s: str, chars: str, vals: List[int]) -> int:
        dp = 0
        ans = 0
        valDict = {}
        for i in range(26):
            valDict[chr(ord("a") + i)] = i + 1
        for i, c in enumerate(chars):
            valDict[c] = vals[i]
        for c in s:
            val = valDict[c]
            dp = max(dp + val, val)
            ans = max(ans, dp)
        return ans
