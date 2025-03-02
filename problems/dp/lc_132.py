from math import inf
from functools import cache


# 超时
class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        ans = None
        min_cnt = inf
        path = []

        def dfs(step: int, cut: int) -> None:
            nonlocal ans
            if step == n:
                if cut < min_cnt:
                    ans = path.copy()
                return

            for i in range(step, n):
                t = s[step : i + 1]
                if t == t[::-1]:
                    path.append(t)
                    dfs(i + 1, cut + 1)
                    path.pop()

        dfs(0, 0)
        return ans


class Solution:
    def minCut(self, s: str) -> int:

        @cache
        def isPalindrome(l: int, r: int) -> bool:
            if l >= r:
                return True
            return s[l] == s[r] and isPalindrome(l + 1, r - 1)

        @cache
        def dfs(i: int) -> int:  # s[0:i+1] 所需的最小分割数
            if isPalindrome(0, i):
                return 0
            res = inf
            for j in range(i, -1, -1):
                if isPalindrome(j, i):
                    res = min(res, dfs(j - 1) + 1)
            return res

        return dfs(len(s) - 1)
