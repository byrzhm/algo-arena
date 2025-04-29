from typing import List


class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        maxval = max(nums)
        n = len(nums)
        ans = cnt = left = 0
        for right, x in enumerate(nums):
            cnt += x == maxval
            # loop invariant: nums[left:right+1] contains k maxvals
            while cnt == k:
                ans += n - right # fix left, nums[left: right+1], ... nums[left:n] contain >= k maxvals
                cnt -= nums[left] == maxval
                left += 1
        return ans

class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        maxval = max(nums)
        ans = cnt = left = 0
        for x in nums:
            cnt += x == maxval
            # loop invariant: nums[left:right+1] contains k maxvals
            while cnt == k:
                cnt -= nums[left] == maxval
                left += 1
            ans += left # fix right, nums[0: right+1], ..., nums[left-1: right+1] contain >= k maxvals
        return ans


nums = [1, 3, 2, 3, 3]
k = 2
print(Solution().countSubarrays(nums, k))
