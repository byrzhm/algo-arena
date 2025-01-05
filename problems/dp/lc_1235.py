from typing import List
import bisect


class Solution:
    # fmt: off
    def jobScheduling(self, startTime: List[int], endTime: List[int], profit: List[int]) -> int:  # fmt: on
        n = len(startTime)
        jobs = sorted(zip(startTime, endTime, profit), key=lambda p: p[1])
        dp = [0] * (n + 1)
        for i in range(1, n + 1):
            k = bisect.bisect_right(jobs, jobs[i - 1][0], hi=i, key=lambda p: p[1]) # 0 <= k <= i
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2])
        return dp[n]
