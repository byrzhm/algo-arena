from typing import List
from collections import Counter


class Solution:
    def numRabbits(self, answers: List[int]) -> int:
        cnt = Counter(answers)
        ans = 0
        for x, c in cnt.items():
            ans += (c + x) // (x + 1) * (x + 1)
        return ans
