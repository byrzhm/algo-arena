from typing import List
from itertools import accumulate
from operator import xor
from collections import defaultdict


class Solution:
    def beautifulSubarrays(self, nums: List[int]) -> int:
        # prefix[0] = 0
        # prefix[i] = nums[0] xor ... nums[i - 1], i > 0
        prefix = list(accumulate(iterable=nums, func=xor, initial=0))
        n = len(nums)
        cnt = 0
        for i in range(n):
            for j in range(i, n):
                if prefix[j + 1] ^ prefix[i] == 0:
                    cnt += 1
        return cnt


nums = [4, 3, 1, 2, 4]
print(Solution().beautifulSubarrays(nums))


class Solution:
    def beautifulSubarrays(self, nums: List[int]) -> int:
        # prefix[0] = 0
        # prefix[i] = nums[0] xor ... nums[i - 1], i > 0
        prefix = list(accumulate(iterable=nums, func=xor, initial=0))
        n = len(nums)
        cnt = 0
        tbl = defaultdict(int)
        tbl[0] = 1
        for i in range(n):
            cnt += tbl[prefix[i + 1]]
            tbl[prefix[i + 1]] += 1
        return cnt


nums = [4, 3, 1, 2, 4]
print(Solution().beautifulSubarrays(nums))


class Solution:
    def beautifulSubarrays(self, nums: List[int]) -> int:
        cnt = defaultdict(int)
        cnt[0] = 1
        ans = 0
        mask = 0
        for x in nums:
            mask ^= x
            ans += cnt[mask]
            cnt[mask] += 1
        return ans


nums = [4, 3, 1, 2, 4]
print(Solution().beautifulSubarrays(nums))
