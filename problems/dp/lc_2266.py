from itertools import groupby


class Solution:
    def countTexts(self, pressedKeys: str) -> int:
        MOD = 1_000_000_007
        charCnt = [3, 3, 3, 3, 3, 4, 3, 4]  # 2-9
        n = len(pressedKeys)
        dp = [1] + [0] * n
        length = 0
        for i in range(1, n + 1):
            c = int(pressedKeys[i - 1]) - int("2")
            if i == 1 or pressedKeys[i - 1] != pressedKeys[i - 2]:
                length = 1
            else:
                length = min(charCnt[c], length + 1)
            for x in range(1, length + 1):
                dp[i] = (dp[i] + dp[i - x]) % MOD
        return dp[n]


MOD = 1_000_000_007
f = [1, 1, 2, 4]
g = [1, 1, 2, 4]
for _ in range(10**5 - 3):
    f.append((f[-1] + f[-2] + f[-3]) % MOD)
    g.append((g[-1] + g[-2] + g[-3] + g[-4]) % MOD)


class Solution:
    def countTexts(self, pressedKeys: str) -> int:
        ans = 1
        for c, s in groupby(pressedKeys):
            m = len(list(s))  # s is an iterable object
            ans = ans * (g[m] if c in "79" else f[m]) % MOD
        return ans
