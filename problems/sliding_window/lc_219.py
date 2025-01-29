from typing import List


class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        n = len(nums)
        tbl = set()
        for i in range(k + 1):
            if i >= n:
                break
            if nums[i] in tbl:
                return True
            tbl.add(nums[i])

        for i in range(k + 1, n):
            tbl.remove(nums[i - k - 1])
            if nums[i] in tbl:
                return True
            tbl.add(nums[i])

        return False
