from typing import List
from functools import cache


class Solution:

    DIRS = [(-1, 0), (0, -1), (1, 0), (0, 1)]

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])

        @cache
        def dfs(x, y):
            best = 1
            for dx, dy in Solution.DIRS:
                x1, y1 = x + dx, y + dy
                if 0 <= x1 < m and 0 <= y1 < n and matrix[x1][y1] > matrix[x][y]:
                    best = max(best, dfs(x1, y1) + 1)
            return best

        ans = 0
        for i in range(m):
            for j in range(n):
                ans = max(ans, dfs(i, j))
        return ans
