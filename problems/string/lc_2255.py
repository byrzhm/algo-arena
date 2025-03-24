from typing import List


class Solution:
    def countPrefixes(self, words: List[str], s: str) -> int:
        n = len(s)

        def isPrefix(pre: str) -> bool:
            m = len(pre)
            if m > n:
                return False

            for i in range(m):
                if s[i] != pre[i]:
                    return False

            return True

        ans = 0
        for w in words:
            if isPrefix(w):
                ans += 1

        return ans


class Solution:
    def countPrefixes(self, words: List[str], s: str) -> int:
        ans = 0
        for word in words:
            if s.startswith(word):
                ans += 1
        return ans
