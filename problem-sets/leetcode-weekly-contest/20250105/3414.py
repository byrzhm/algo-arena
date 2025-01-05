from typing import List
import bisect

"""
Two intervals are said to be non-overlapping if they do not share any points.
In particular, intervals sharing a left or right boundary are considered overlapping.

-> bisect_left
"""

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        arr = sorted(
            [(l, r, w, i) for i, (l, r, w) in enumerate(intervals)], key=lambda p: p[1]
        )
        dp = [[(0, []) for _ in range(5)] for _ in range(n + 1)]
        for i in range(1, n + 1):
            k = bisect.bisect_left(arr, arr[i - 1][0], hi=i, key=lambda p: p[1])
            for j in range(1, 5):
                s2, id2 = dp[k][j - 1]
                dp[i][j] = min(dp[i - 1][j], (s2 - arr[i - 1][2], sorted(id2 + [arr[i - 1][-1]])))
        return dp[-1][4][1]


# fmt: off
intervals = [[1, 3, 2], [4, 5, 2], [1, 5, 5], [6, 9, 3], [6, 7, 1], [8, 9, 1]]
assert Solution().maximumWeight(intervals) == [2, 3]

intervals = [[5, 8, 1], [6, 7, 7], [4, 7, 3], [9, 10, 6], [7, 8, 2], [11, 14, 3], [3, 5, 5]]
assert Solution().maximumWeight(intervals) == [1, 3, 5, 6]

intervals = [[1, 1, 1000000000], [1, 1, 1000000000], [1, 1, 1000000000], [1, 1, 1000000000]]
assert Solution().maximumWeight(intervals) == [0]
# fmt: on
