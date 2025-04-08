from typing import List
from collections import Counter


class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        cnt = Counter(nums)
        i = ans = 0
        n = len(nums)
        keys = list(cnt.keys())
        for k in keys:
            while k in cnt and cnt[k] > 1:
                ans += 1
                for _ in range(3):
                    if i >= n:
                        break

                    t = nums[i]
                    cnt[t] -= 1
                    if cnt[t] == 0:
                        del cnt[t]
                    i += 1
        return ans


"""
remove [0:j], j is a multiple of 3 and j > i
if i // 3 = k, then i = 3k or 3k+1 or 3k+2
so 3k <= i < 3k + 3, 
j should be 3k + 3
the answer would be j // 3 = k + 1 = i // 3 + 1
"""


class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        seen = set()
        for i in range(len(nums) - 1, -1, -1):
            x = nums[i]
            if x in seen:
                return i // 3 + 1
            seen.add(x)
        return 0


nums = [1, 2, 3, 4, 2, 3, 3, 5, 7]
print(Solution().minimumOperations(nums))
