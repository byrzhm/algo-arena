from typing import List


class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        # return sorted(nums)[len(nums)//2]
        n = len(nums)
        nums.sort()
        return nums[n // 2]


class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        candidate: int
        count = 0
        for x in nums:
            if count == 0:
                candidate = x
            count += +1 if x == candidate else -1
        return candidate
