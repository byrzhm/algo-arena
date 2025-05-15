from typing import List


class Solution:
    def getLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        idxs = [0]
        prev = groups[0]
        for i in range(1, len(groups)):
            if groups[i] != prev:
                idxs.append(i)
                prev = groups[i]
        return [words[i] for i in idxs]
