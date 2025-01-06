from typing import List
from collections import Counter


class Solution:
    def maximumTotalDamage(self, power: List[int]) -> int:
        cnt = Counter(power)
        sortedKeys = sorted(cnt.keys())
        n = len(sortedKeys)
        dp = [0] * (n + 1)
        j = 0
        for i, x in enumerate(sortedKeys):
            while sortedKeys[j] < x - 2:  # sortedKeys[j] will be the first >= x - 2
                j += 1
            dp[i + 1] = max(dp[i], dp[j] + cnt[x] * x)

        return dp[-1]
