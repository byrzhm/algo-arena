from typing import List

# fmt: off
class Solution:
    def minimumCost(self, m: int, n: int, hCut: List[int], vCut: List[int]) -> int:
        hCut.sort(), vCut.sort()
        h, v = 1, 1
        min_cost = 0
        while hCut or vCut:
            if not vCut or (hCut and hCut[-1] > vCut[-1]):
                min_cost += hCut.pop() * h
                v += 1
            else:
                min_cost += vCut.pop() * v
                h += 1
        return min_cost
# fmt: on

m, n = 3, 2
horizontalCut = [1, 3]
verticalCut = [5]
# print(Solution().minimumCost(m, n, horizontalCut, verticalCut)) # should be 13
assert Solution().minimumCost(m, n, horizontalCut, verticalCut) == 13