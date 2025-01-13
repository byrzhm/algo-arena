from typing import List
from functools import cache


class Solution:
    DIRS = [(-1, 0), (0, -1), (0, 1), (1, 0)]

    def countPaths(self, grid: List[List[int]]) -> int:
        MOD = 1_000_000_007
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(x, y) -> int:
            total = 1
            for dx, dy in Solution.DIRS:
                x1, y1 = x + dx, y + dy
                if 0 <= x1 < m and 0 <= y1 < n and grid[x1][y1] < grid[x][y]:
                    total += dfs(x1, y1)
            return total

        ans = 0
        for i in range(m):
            for j in range(n):
                ans = (ans + dfs(i, j)) % MOD

        return ans
