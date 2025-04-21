from typing import List


# fmt: off
class Solution:
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:
        rel_max = rel_min = x = 0
        for d in differences:
            x += d
            if x > rel_max: rel_max = x
            if x < rel_min: rel_min = x
        return max(0, upper - lower - (rel_max - rel_min) + 1)
# fmt: on
