from collections import Counter

"""
1 <= s.length <= 10^5
"""


class Solution:
    def minAnagramLength(self, s: str) -> int:
        n = len(s)

        def check(m):
            hashtbl = Counter(s[:m])
            for i in range(m, n, m):
                tmp_tbl = {}
                for j in range(i, i + m):
                    if s[j] not in tmp_tbl:
                        tmp_tbl[s[j]] = 1
                    else:
                        tmp_tbl[s[j]] += 1
                    if s[j] not in hashtbl or tmp_tbl[s[j]] > hashtbl[s[j]]:
                        return False
                if len(tmp_tbl) != len(hashtbl):
                    return False
            return True

        for i in range(1, n):
            if n % i != 0:
                continue
            if check(i):
                return i
        return n


s = "abba"
assert Solution().minAnagramLength(s) == 2

s = "cdef"
assert Solution().minAnagramLength(s) == 4
