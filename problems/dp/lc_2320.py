from functools import cache


class Solution:
    def countHousePlacements(self, n: int) -> int:
        MOD = 1_000_000_007

        @cache
        def dfs(i):
            if i == 0:
                return 1
            if i == 1:
                return 2
            return dfs(i - 1) + dfs(i - 2)

        return dfs(n) ** 2 % MOD


"""
pre-calculate
"""

MOD = 1_000_000_007
f = [1, 2]
for _ in range(10**4 - 1):
    f.append((f[-1] + f[-2]) % MOD)


class Solution:
    def countHousePlacements(self, n: int) -> int:
        return f[n] ** 2 % MOD
