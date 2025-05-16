from typing import List

# fmt: off
class Solution:
    def getWordsInLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        def check(s1: str, s2: str) -> int:
            return len(s1) == len(s2) and sum(c1 != c2 for c1, c2 in zip(s1, s2)) == 1

        n = len(groups)
        dp = [1] * n
        prev_ = [-1] * n
        max_index = 0

        for i in range(1, n):
            for j in range(i):
                if check(words[i], words[j]) == 1 and dp[j] + 1 > dp[i] and groups[i] != groups[j]:
                    dp[i] = dp[j] + 1
                    prev_[i] = j
            if dp[i] > dp[max_index]:
                max_index = i
        
        ans = []
        i = max_index
        while i >= 0:
            ans.append(words[i])
            i = prev_[i]
        ans.reverse()
        return ans
# fmt: on
