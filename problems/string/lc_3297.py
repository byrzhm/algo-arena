from collections import defaultdict


class Solution:
    def validSubstringCount(self, word1: str, word2: str) -> int:
        n1, n2 = len(word1), len(word2)

        if n1 < n2:
            return 0

        counter = defaultdict(int)
        for c in word2:
            counter[c] -= 1
        less = len(counter)

        ans = left = 0

        for c in word1:
            counter[c] += 1
            if counter[c] == 0:
                less -= 1
            while less == 0:
                if counter[word1[left]] == 0:
                    less += 1
                counter[word1[left]] -= 1
                left += 1
            ans += left

        return ans
