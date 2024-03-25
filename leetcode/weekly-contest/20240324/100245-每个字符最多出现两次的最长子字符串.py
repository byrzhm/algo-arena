from collections import Counter

class Solution:
    def maximumLengthSubstring(self, s: str) -> int:
        cnt = Counter()
        maxLen = -1
        j = 0
        for i, c in enumerate(s):
            while cnt[c] == 2:
                cnt[s[j]] -= 1
                j += 1
            cnt[c] += 1
            maxLen = max(maxLen, i - j + 1)

        return maxLen
            