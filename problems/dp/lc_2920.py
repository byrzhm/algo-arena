from typing import List
from functools import cache


class Solution:
    def maximumPoints(self, edges: List[List[int]], coins: List[int], k: int) -> int:
        n = len(coins)
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        @cache
        def dfs(i: int, j: int, fa: int):
            res1 = (coins[i] >> j) - k
            res2 = coins[i] >> (j + 1)
            for ch in g[i]:
                if ch != fa:
                    res1 += dfs(ch, j, i)
                    if j < 14: # 13
                        res2 += dfs(ch, j + 1, i)
            return max(res1, res2)

        return dfs(0, 0, -1)
