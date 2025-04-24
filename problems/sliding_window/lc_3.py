from collections import defaultdict


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        tbl = defaultdict(int)
        left = 0
        ans = 0
        for right, x in enumerate(s):
            tbl[x] += 1
            while tbl[x] > 1:
                tbl[s[left]] -= 1
                left += 1
            ans = max(ans, right - left + 1)
        return ans
