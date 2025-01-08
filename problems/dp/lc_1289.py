from typing import List
from math import inf


class Solution:
    def minFallingPathSum(self, grid: List[List[int]]) -> int:
        n = len(grid)
        dp = [[0] * n for _ in range(n)]
        for j in range(n):
            dp[0][j] = grid[0][j]

        for i in range(1, n):
            for j in range(n):
                dp[i][j] = min(dp[i - 1][k] for k in range(n) if k != j) + grid[i][j]

        return min(dp[-1])
