from typing import List
import math
from functools import reduce


class Solution:
    def maxLength(self, nums: List[int]) -> int:
        def check(l: int, r: int) -> bool:
            prod = math.prod(nums[l : r + 1])
            gcd = reduce(math.gcd, nums[l : r + 1])
            lcm_ = reduce(math.lcm, nums[l : r + 1])
            return prod == gcd * lcm_

        curr_max = 0
        n = len(nums)
        for i in range(n):
            for j in range(n - 1, i, -1):
                if check(i, j):
                    curr_max = max(curr_max, j - i + 1)
                    break
        return curr_max
