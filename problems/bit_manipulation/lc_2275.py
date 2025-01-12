from typing import List


class Solution:
    def largestCombination(self, candidates: List[int]) -> int:
        maxVal = max(candidates)
        ans = -1
        b = 1
        while b <= maxVal:
            ans = max(ans, sum(map(lambda x: 1 if x & b else 0, candidates)))
            b *= 2
        return ans

        # return max((l.count('1') for l in zip(*(bin(x)[2:].zfill(24) for x in candidates))))


candidates = [16, 17, 71, 62, 12, 24, 14]
print(Solution().largestCombination(candidates))

candidates = [8, 8]
print(Solution().largestCombination(candidates))
