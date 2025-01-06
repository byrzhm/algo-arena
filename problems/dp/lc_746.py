from typing import List


"""
dp[i] contains cost[i]
"""


class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        n = len(cost)
        cost.append(0)
        dp = [0] * (n + 1)
        dp[0], dp[1] = cost[0], cost[1]
        for i in range(2, n + 1):
            dp[i] = min(dp[i - 2], dp[i - 1]) + cost[i]
        return dp[-1]


class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        n = len(cost)
        cost.append(0)
        p, q, r = 0, cost[0], cost[1]
        for i in range(2, n + 1):
            p = q
            q = r
            r = min(p, q) + cost[i]
        return r


"""
dp[i] does not contain cost[i]
"""


class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        n = len(cost)
        dp = [0] * (n + 1)
        for i in range(2, n + 1):
            dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1])
        return dp[n]


class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        n = len(cost)
        p, q, r = 0, 0, 0
        for i in range(2, n + 1):
            p = q
            q = r
            r = min(p + cost[i - 2], q + cost[i - 1])
        return r
