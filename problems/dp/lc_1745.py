from functools import cache, reduce
from operator import or_


class Solution:
    def checkPartitioning(self, s: str) -> bool:
        @cache
        def isPalindrome(l: int, r: int) -> bool:
            if l >= r:
                return True
            return s[l] == s[r] and isPalindrome(l + 1, r - 1)

        # 将 s[:r+1] 切 i 刀, 划分成 i + 1 个子串都是回文串
        @cache
        def dfs(i: int, r: int) -> bool:
            if i == 0:
                return isPalindrome(0, r)
            return reduce(
                or_,
                [isPalindrome(l, r) and dfs(i - 1, l - 1) for l in range(i, r + 1)],
                False,
            )

        # for i in range(3):
        #     for j in range(len(s)):
        #         print(f"dfs({i}, {j}) = {dfs(i, j)}, s[:{j+1}]={s[:j+1]}")

        return dfs(2, len(s) - 1)
