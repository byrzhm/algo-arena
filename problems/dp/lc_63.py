from typing import List


class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        r, c = len(obstacleGrid), len(obstacleGrid[0])
        dp = [[0] * c for _ in range(r)]

        for i in range(r):
            if obstacleGrid[i][0]:
                break
            dp[i][0] = 1

        for j in range(c):
            if obstacleGrid[0][j]:
                break
            dp[0][j] = 1

        for i in range(1, r):
            for j in range(1, c):
                if obstacleGrid[i][j] != 1:
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
        return dp[-1][-1]
