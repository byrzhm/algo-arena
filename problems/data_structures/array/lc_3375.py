from typing import List
import bisect


class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        nums = list(set(nums))
        nums.sort()
        n = len(nums)
        idx = bisect.bisect_left(nums, k)
        return -1 if idx > 0 else (n - 1 if nums[0] == k else n)


class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        min_elem = min(nums)
        if min_elem < k:
            return -1
        return len(set(nums)) - (min_elem == k)


nums = [10, 2]
k = 2
print(Solution().minOperations(nums, k))
