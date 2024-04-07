from math import inf
from typing import List
# from functools import cache

# class Solution:
#     def maxProfit(self, prices: List[int]) -> int:
#         n = len(prices)

#         # !python version >= 3.9
#         @cache
#         def dfs(i, hold):
#             if i < 0:
#                 return -inf if hold else 0
#             if hold:
#                 return max(dfs(i - 1, 1), dfs(i - 1, 0) - prices[i])
#             else:
#                 return max(dfs(i - 1, 0), dfs(i - 1, 1) + prices[i])

#         return dfs(n - 1, False)

# print(Solution().maxProfit([7,1,5,3,6,4]))

"""

dp[0][0] = 0
dp[0][1] = -inf

dp[i + 1][0] = max(dp[i][0], dp[i][1] + prices[i + 1])
dp[i + 1][1] = max(dp[i][1], dp[i][0] - prices[i + 1])

"""

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        f0, f1 = 0, -inf

        for price in prices:
            new_f0 = max(f0, f1 + price)
            new_f1 = max(f1, f0 - price)
            f0 = new_f0
            f1 = new_f1

        return f0

print(Solution().maxProfit([7,1,5,3,6,4]))