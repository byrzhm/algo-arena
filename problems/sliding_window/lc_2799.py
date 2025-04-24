from typing import List
from collections import defaultdict


# Wrong Answer
class Solution:
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        tot = len(set(nums))
        tbl = defaultdict(int)
        ans = left = 0
        for x in nums:
            tbl[x] += 1
            if len(tbl) == tot:  # remove this
                while len(tbl) == tot:
                    tbl[nums[left]] -= 1
                    if tbl[nums[left]] == 0:
                        del tbl[nums[left]]
                    left += 1
                ans += left
        return ans


class Solution:
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        tot = len(set(nums))
        tbl = defaultdict(int)
        ans = left = 0
        for x in nums:
            tbl[x] += 1
            while len(tbl) == tot:
                tbl[nums[left]] -= 1
                if tbl[nums[left]] == 0:
                    del tbl[nums[left]]
                left += 1
            ans += left
        return ans


nums = [1, 3, 1, 2, 2]
print(Solution().countCompleteSubarrays(nums))
