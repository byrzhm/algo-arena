from collections import defaultdict


class Solution:
    def countBalls(self, lowLimit: int, highLimit: int) -> int:
        def sumDigits(x: int) -> int:
            res = 0
            while x > 0:
                res += x % 10
                x //= 10
            return res

        cnt = defaultdict(int)
        ans = -1
        for x in range(lowLimit, highLimit + 1):
            s = sumDigits(x)
            cnt[s] += 1
            ans = max(ans, cnt[s])
        return ans
