from typing import List
from math import inf


class Solution:
    def maxSubarraySumCircular(self, nums: List[int]) -> int:
        s = 0
        max_s, min_s = -inf, inf
        f_max, f_min = 0, 0
        for x in nums:
            f_max = max(f_max, 0) + x
            f_min = min(f_min, 0) + x
            max_s = max(max_s, f_max)
            min_s = min(min_s, f_min)
            s += x
        if s == min_s:
            return max_s
        return max(max_s, s - min_s)
