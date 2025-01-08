from typing import List
from math import inf


class Solution:
    def maxMoves(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        dp = [[False] * n for _ in range(m)]
        for i in range(m):
            dp[i][0] = True

        ans = 0
        for j in range(1, n):
            for i in range(m):
                min_ = grid[i][j - 1] if dp[i][j - 1] else inf
                if i > 0 and dp[i - 1][j - 1]:
                    min_ = min(min_, grid[i - 1][j - 1])
                if i < m - 1 and dp[i + 1][j - 1]:
                    min_ = min(min_, grid[i + 1][j - 1])
                if grid[i][j] > min_:
                    dp[i][j] = True
                    ans = j

        return ans
