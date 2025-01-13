# StackOverflow: Difference between zip(list) and zip(*list) [duplicate]
# https://stackoverflow.com/questions/29139350/difference-between-ziplist-and-ziplist
from typing import List
from functools import cache
from math import inf


# fmt: off
class Solution:
    def maxCollectedFruits(self, fruits: List[List[int]]) -> int:
        n = len(fruits)

        @cache
        def dfs(i: int, j: int) -> int:
            if not (n - 1 - i <= j < n):
                return -inf
            if i == 0:
                return fruits[0][-1]
            return max(dfs(i - 1, j - 1), dfs(i - 1, j), dfs(i - 1, j + 1)) + fruits[i][j]

        ans = sum(row[i] for i, row in enumerate(fruits))
        ans += dfs(n - 2, n - 1)
        dfs.cache_clear()
        fruits = list(zip(*fruits))
        ans += dfs(n - 2, n - 1)
        return ans
# fmt: on
