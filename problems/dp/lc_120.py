from typing import List
from math import inf


class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        dp = [[0] * k for k in range(1, n + 1)]
        dp[0][0] = triangle[0][0]
        for i in range(1, n):
            dp[i][0] = dp[i - 1][0] + triangle[i][0]
            dp[i][-1] = dp[i - 1][-1] + triangle[i][-1]

        for i in range(1, n):
            for j in range(1, i):
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j]
        
        # last layer
        ans = inf
        for j in range(n):
            if j != 0 and j != n - 1:
                dp[-1][j] = min(dp[-2][j - 1], dp[-2][j]) + triangle[-1][j]
            ans = min(dp[-1][j], ans)
        return ans
