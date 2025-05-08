from typing import List
from math import inf
from heapq import heappop, heappush


class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        n, m = len(moveTime), len(moveTime[0])
        dis = [[inf] * m for _ in range(n)]
        dis[0][0] = 0
        h = [(0, 0, 0)]
        while True:
            d, i, j = heappop(h)
            if i == n - 1 and j == m - 1:
                return d
            if d > dis[i][j]:
                continue
            time = (i + j) % 2 + 1
            for x, y in (i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1):  # 枚举周围四个格子
                if 0 <= x < n and 0 <= y < m:
                    new_dis = max(d, moveTime[x][y]) + time
                    if new_dis < dis[x][y]:
                        dis[x][y] = new_dis
                        heappush(h, (new_dis, x, y))
