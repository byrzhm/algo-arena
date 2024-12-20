from math import inf
from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        ans = -inf
        currMin = inf
        for price in prices:
            currMin = min(currMin, price)
            ans = max(ans, price - currMin)

        return ans
