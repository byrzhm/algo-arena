MOD = 1_000_000_007
f = [0] * 1001
f[0] = 0
f[1] = 1
f[2] = 2
f[3] = 5
for i in range(4, 1001):
    f[i] = (2 * f[i - 1] + f[i - 3]) % MOD


class Solution:
    def numTilings(self, n: int) -> int:
        return f[n]
