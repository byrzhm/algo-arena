from typing import List
from functools import cache
from math import inf

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        @cache
        def dfs(i, j, hold):
            if i < 0:
                return -inf if hold else 0
            if j < 0:
                return -inf
            if hold:
                return max(dfs(i - 1, j, True), dfs(i - 1, j, False) - prices[i])
            return max(dfs(i - 1, j, False), dfs(i - 1, j - 1, True) + prices[i])
            
        return dfs(n - 1, 2, 0) 

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        k = 2
        f = [[-inf] * 2 for _ in range(k + 2)]
        for j in range(1, k + 2):
            f[j][0] = 0
        for p in prices:
            for j in range(k + 1, 0, -1):
                f[j][1] = max(f[j][1], f[j][0] - p)
                f[j][0] = max(f[j][0], f[j - 1][1] + p)

        return f[-1][0]