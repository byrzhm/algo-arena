from typing import List


class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        if not nums:
            return 0

        n = len(nums)
        fast = slow = 1
        while fast < n:
            if nums[fast - 1] != nums[fast]: # nums[slow - 1] != nums[fast]
                nums[slow] = nums[fast]
                slow += 1
            fast += 1
        return slow
