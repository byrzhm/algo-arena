from typing import List


class Solution:
    def numberOfPaths(self, grid: List[List[int]], k: int) -> int:
        MOD = 1_000_000_007
        m, n = len(grid), len(grid[0])
        dp = [[[0] * k for _ in range(n)] for _ in range(m)]
        dp[0][0][grid[0][0] % k] += 1

        for i in range(1, m):
            for t in range(k):
                dp[i][0][(t + grid[i][0]) % k] += dp[i - 1][0][t]

        for j in range(1, n):
            for t in range(k):
                dp[0][j][(t + grid[0][j]) % k] += dp[0][j - 1][t]

        for i in range(1, m):
            for j in range(1, n):
                for t in range(k):
                    dp[i][j][(t + grid[i][j]) % k] += dp[i - 1][j][t] + dp[i][j - 1][t]
        
        return dp[-1][-1][0] % MOD
