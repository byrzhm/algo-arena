from typing import List


class Solution:
    def maximumOr(self, nums: List[int], k: int) -> int:
        all_or = fixed = 0
        for x in nums:
            fixed |= all_or & x
            all_or |= x
        return max(x << k | all_or ^ x | fixed for x in nums)

nums = [12, 9]
k = 1
ans = Solution().maximumOr(nums, k)
assert ans == 30, f"Expected {30}, got {ans}"
