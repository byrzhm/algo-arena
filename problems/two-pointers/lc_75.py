from typing import List


class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        i, left, right = 0, 0, n - 1
        while i <= right:
            while i < right and nums[i] == 2:
                nums[right], nums[i] = nums[i], nums[right]
                right -= 1
            if nums[i] == 0:
                nums[left], nums[i] = nums[i], nums[left]
                left += 1
            i += 1


nums = [2, 0, 2, 1, 1, 0]
Solution().sortColors(nums)
print(nums)
