from typing import List

# fmt: off
class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        MOD = 1_000_000_007
        m, n = len(grid), len(grid[0])
        minProd = [[0] * n for _ in range(m)]
        maxProd = [[-1] * n for _ in range(m)]

        minProd[0][0] = maxProd[0][0] = grid[0][0]
        for i in range(1, m):
            minProd[i][0] = minProd[i - 1][0] * grid[i][0]
            maxProd[i][0] = maxProd[i - 1][0] * grid[i][0]
        for j in range(1, n):
            minProd[0][j] = minProd[0][j - 1] * grid[0][j]
            maxProd[0][j] = maxProd[0][j - 1] * grid[0][j]

        for i in range(1, m):
            for j in range(1, n):
                if grid[i][j] > 0:
                    minProd[i][j] = min(minProd[i - 1][j], minProd[i][j - 1]) * grid[i][j]
                    maxProd[i][j] = max(maxProd[i - 1][j], maxProd[i][j - 1]) * grid[i][j]
                elif grid[i][j] < 0:
                    minProd[i][j] = max(maxProd[i - 1][j], maxProd[i][j - 1]) * grid[i][j]
                    maxProd[i][j] = min(minProd[i - 1][j], minProd[i][j - 1]) * grid[i][j]
                else:
                    minProd[i][j], maxProd[i][j] = 0, 0
        if maxProd[-1][-1] < 0:
            return -1
        return maxProd[-1][-1] % MOD
# fmt: on
