from typing import List
from functools import cache
from math import inf


# fmt: off
class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(t: int, x0: int, x1: int) -> int:
            if not (0 <= x0 < n and 0 <= x1 < n):
                return -inf
            if t == 0:
                return (grid[0][0] + grid[0][-1]) if x0 == 0 and x1 == n - 1 else -inf
            return max(
                dfs(t - 1, x0 + dx0, x1 + dx1) for dx0 in (-1, 0, 1) for dx1 in (-1, 0, 1)
            ) + grid[t][x0] + (grid[t][x1] if x0 != x1 else 0)

        ans = 0
        for x0 in range(n):
            for x1 in range(x0, n):
                ans = max(ans, dfs(m - 1, x0, x1))
        return ans
# fmt: on



# fmt: off
class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(i: int, j: int, k: int) -> int:
            if i == m or j < 0 or j >= n or k < 0 or k >= n:
                return 0
            return max(
                dfs(i + 1, j2, k2) for j2 in (j - 1, j, j + 1) for k2 in (k - 1, k, k + 1)
            ) + grid[i][j] + (grid[i][k] if j != k else 0)

        return dfs(0, 0, n - 1)
# fmt: on
