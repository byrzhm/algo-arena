from typing import List
from functools import cache


class Solution:

    DIRS = [(1, 0), (0, 1)]

    def hasValidPath(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        if grid[0][0] == ")" or grid[-1][-1] == "(" or (m + n) % 2 == 0:
            return False

        @cache
        def dfs(x, y, c):
            if c > m + n - x - y - 1:
                return False
            if x == m - 1 and y == n - 1:
                return c == 1
            c += 1 if grid[x][y] == "(" else -1
            if c >= 0:
                for dx, dy in Solution.DIRS:
                    x1, y1 = x + dx, y + dy
                    if x1 < m and y1 < n and dfs(x1, y1, c):
                        return True
            return False

        return dfs(0, 0, 0)
