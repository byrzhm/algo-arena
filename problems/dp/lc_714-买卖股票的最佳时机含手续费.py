from typing import List
from functools import cache
from math import inf

class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        n = len(prices)
        @cache
        def dfs(i, hold):
            if i < 0:
                return -inf if hold else 0
            if hold:
                return max(dfs(i - 1, True), dfs(i - 1, False) - prices[i])
            return max(dfs(i - 1, False), dfs(i - 1, True) + prices[i] - fee)

        return dfs(n - 1, False)

class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        n = len(prices)
        f = [[-inf] * 2 for _ in range(n + 1)]
        f[0][0] = 0
        for i in range(1, n + 1):
            f[i][0] = max(f[i - 1][0], f[i - 1][1] + prices[i - 1] - fee)
            f[i][1] = max(f[i - 1][1], f[i - 1][0] - prices[i - 1])

        return f[n][0]


class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        f0, f1 = 0, -inf
        for p in prices:
            new_f0 = max(f0, f1 + p - fee)
            new_f1 = max(f1, f0 - p)
            f0 = new_f0
            f1 = new_f1
        return f0
        