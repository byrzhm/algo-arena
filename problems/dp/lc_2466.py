class Solution:
    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:
        dp = [1] + [0] * high
        for i in range(1, high + 1):
            x = dp[i - zero] if i >= zero else 0
            y = dp[i - one] if i >= one else 0
            dp[i] = x + y
        return sum(dp[low : high + 1]) % (10 ** 9 + 7)
