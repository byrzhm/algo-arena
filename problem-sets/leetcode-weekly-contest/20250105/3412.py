class Solution:
    def calculateScore(self, s: str) -> int:
        stk = [[] for _ in range(26)]

        def mirror(ascii: int):
            return 25 - ascii

        ans = 0
        for i, c in enumerate(s):
            c = ord(c) - ord("a")
            m = mirror(c)
            if len(stk[m]) > 0:
                j = stk[m].pop()
                ans += i - j
            else:
                stk[c].append(i)
        return ans
