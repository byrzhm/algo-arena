from functools import cache


class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        @cache
        def makePalindrome(l: int, r: int):
            return 0 if l >= r else (makePalindrome(l + 1, r - 1) + (1 if s[l] != s[r] else 0))
        
        @cache
        def dfs(i: int, r: int) -> int:
        # 把 s[:r+1] 切 i 刀，分成 i+1 个子串，每个子串改成回文串的最小总修改次数
            if i == 0:
                return makePalindrome(0, r)
            return min(dfs(i - 1, l - 1) + makePalindrome(l, r)
                       for l in range(i, r + 1))
        
        return dfs(k - 1, len(s) - 1)