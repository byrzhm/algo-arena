from typing import List
from functools import cache
from math import inf


# fmt: off
class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        n = len(grid)

        @cache
        def dfs(t: int, j: int, k: int) -> int:
            if (
                j < 0
                or k < 0
                or t < j
                or t < k
                or grid[t - j][j] < 0
                or grid[t - k][k] < 0
            ):
                return -inf
            if t == 0:
                return grid[0][0]
            return (
                max(
                    dfs(t - 1, j, k),
                    dfs(t - 1, j, k - 1),
                    dfs(t - 1, j - 1, k),
                    dfs(t - 1, j - 1, k - 1),
                ) + grid[t - j][j] + (grid[t - k][k] if j != k else 0)
            )

        return max(dfs(2 * n - 2, n - 1, n - 1), 0)
# fmt: on
