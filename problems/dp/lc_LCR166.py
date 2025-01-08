from typing import List


class Solution:
    def jewelleryValue(self, frame: List[List[int]]) -> int:
        r, c = len(frame), len(frame[0])
        dp = [[0] * c for _ in range(r)]
        dp[0][0] = frame[0][0]
        for i in range(1, r):
            dp[i][0] = dp[i - 1][0] + frame[i][0]
        for j in range(1, c):
            dp[0][j] = dp[0][j - 1] + frame[0][j]

        for i in range(1, r):
            for j in range(1, c):
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + frame[i][j]
        return dp[-1][-1]
