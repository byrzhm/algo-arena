from typing import List
from math import inf


# Wrong Solution
class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        m, n = len(points), len(points[0])
        maxTrack = [[[-1, 0] for _ in range(n)] for _ in range(m)]

        def dfs(x, y, t):
            if t < maxTrack[x][y][0]:
                return -inf
            elif t == maxTrack[x][y][0]:
                return maxTrack[x][y][1]

            maxTrack[x][y][0] = t
            acc = t + points[x][y]
            if x == m - 1:
                maxTrack[x][y][1] = acc
                return maxTrack[x][y][1]

            maxTrack[x][y][1] = max(dfs(x + 1, j, acc - abs(j - y)) for j in range(n))
            return maxTrack[x][y][1]

        return max(dfs(0, j, 0) for j in range(n))


# Accepted Solution
class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        m, n = len(points), len(points[0])
        f = [0] * n
        for i in range(m):
            g = [0] * n
            best = -inf
            for j in range(n):
                best = max(best, f[j] + j)
                g[j] = max(g[j], best + points[i][j] - j)
            best = -inf
            for j in range(n - 1, -1, -1):
                best = max(best, f[j] - j)
                g[j] = max(g[j], best + points[i][j] + j)
            f = g
        return max(f)
