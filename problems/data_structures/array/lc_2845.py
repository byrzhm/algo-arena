from typing import List
from itertools import accumulate


class Solution:
    def countInterestingSubarrays(self, nums: List[int], modulo: int, k: int) -> int:
        pre_sum = list(accumulate((x % modulo == k for x in nums), initial=0))
        cnt = [0] * min(len(nums) + 1, modulo)
        ans = 0
        for s in pre_sum:
            if s >= k:
                ans += cnt[(s - k) % modulo]
            cnt[s % modulo] += 1
        return ans
