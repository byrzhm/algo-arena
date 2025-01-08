from typing import List


class Solution:
    def minFallingPathSum(self, matrix: List[List[int]]) -> int:
        n = len(matrix)
        dp = [[0] * n for _ in range(n)]
        for j in range(n):
            dp[0][j] = matrix[0][j]
        for i in range(1, n):
            for j in range(n):
                dp[i][j] = dp[i - 1][j]
                if j > 0:
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1])
                if j < n - 1:
                    dp[i][j] = min(dp[i][j], dp[i - 1][j + 1])
                dp[i][j] += matrix[i][j]

        return min(dp[-1])
