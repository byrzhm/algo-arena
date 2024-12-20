from typing import List


# class Solution:
#     def maxProfit(self, prices: List[int]) -> int:
#         n = len(prices)
        
#         @cache
#         def dfs(i, hold):
#             if i < 0:
#                 return -inf if hold else 0
#             if hold:
#                 return max(dfs(i - 1, True), dfs(i - 2, False) - prices[i])
#             return max(dfs(i - 1, False), dfs(i - 1, True) + prices[i])

#         return dfs(n - 1, False)


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        if len(prices) == 0:
            return 0

        f0 = 0
        f1 = 0
        f2 = -prices[0]

        for p in prices:
            new_f1 = max(f1, f2 + p)
            new_f2 = max(f2, f0 - p)
            f0 = f1
            f1 = new_f1
            f2 = new_f2

        return f1

        