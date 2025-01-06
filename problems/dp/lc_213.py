from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        def rob0(nums: List[int]) -> int:
            n = len(nums)
            p, q, r = 0, 0, 0
            for i in range(1, n + 1):
                p = q
                q = r
                r = max(q, p + nums[i - 1])
            return r

        return max(rob0(nums[1:]), nums[0] + rob0(nums[2:-1]))
