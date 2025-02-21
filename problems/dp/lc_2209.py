from functools import cache


class Solution:
    def minimumWhiteTiles(self, floor: str, numCarpets: int, carpetLen: int) -> int:
        floor = list(map(int, floor))
        @cache
        def dfs(i: int, j: int) -> int:
            if carpetLen * i > j:  # 剩余砖块可以全部覆盖
                return 0
            if i == 0:
                return dfs(i, j - 1) + floor[j]
            return min(dfs(i, j - 1) + floor[j], dfs(i - 1, j - carpetLen))
        return dfs(numCarpets, len(floor) - 1)
