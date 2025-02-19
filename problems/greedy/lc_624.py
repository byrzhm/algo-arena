from typing import List
from math import inf


class Solution:
    def maxDistance(self, arrays: List[List[int]]) -> int:
        ans = 0
        cur_min, cur_max = inf, -inf
        for arr in arrays:
            ans = max(arr[-1] - cur_min, cur_max - arr[0], ans)
            cur_max = max(cur_max, arr[-1])
            cur_min = min(cur_min, arr[0])
        return ans
