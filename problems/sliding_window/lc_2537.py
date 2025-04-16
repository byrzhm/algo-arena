from typing import List
from collections import defaultdict


class Solution:
    def countGood(self, nums: List[int], k: int) -> int:
        cnt = defaultdict(int)  # 比 Counter() 快
        ans = left = pairs = 0
        for x in nums:
            pairs += cnt[x]
            cnt[x] += 1
            while pairs >= k:
                cnt[nums[left]] -= 1
                pairs -= cnt[nums[left]]
                left += 1
            ans += left
        return ans
