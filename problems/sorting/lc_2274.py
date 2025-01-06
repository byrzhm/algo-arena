from typing import List
from itertools import pairwise


class Solution:
    def maxConsecutive(self, bottom: int, top: int, special: List[int]) -> int:
        special.extend([bottom - 1, top + 1])
        special.sort()

        n = len(special)
        ans = 0
        for i in range(n - 1):
            ans = max(ans, special[i + 1] - special[i] - 1)
        return ans


# One line
# fmt: off
class Solution:
    def maxConsecutive(self, bottom: int, top: int, special: List[int]) -> int:
        return max([y - x - 1 for x, y in pairwise(sorted(special + [bottom - 1, top + 1]))])
# fmt: on
