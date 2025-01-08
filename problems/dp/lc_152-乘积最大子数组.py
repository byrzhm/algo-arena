from typing import List


class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        f_min = f_max = max_p = nums[0]
        for x in nums[1:]:
            f_max, f_min = max(f_max * x, f_min * x, x), min(f_min * x, f_max * x, x)
            max_p = max(max_p, f_max)
        return max_p
