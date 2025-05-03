from typing import List
from math import inf


class Solution:
    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:
        ans = inf
        for i in range(1, 7):
            xt = xb = 0
            for t, b in zip(tops, bottoms):
                if t != i and b != i:
                    break
                if t != i:  # b == i
                    xt += 1
                if b != i:  # t == i
                    xb += 1
            else:  # no break
                x = xt if xt < xb else xb
                ans = ans if ans < x else x

        return ans if ans < inf else -1


class Solution:
    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:
        ans = inf
        for i in [tops[0], bottoms[0]]:
            xt = xb = 0
            for t, b in zip(tops, bottoms):
                if t != i and b != i:
                    break
                if t != i:  # b == i
                    xt += 1
                if b != i:  # t == i
                    xb += 1
            else:  # no break
                x = xt if xt < xb else xb
                ans = ans if ans < x else x

        return ans if ans < inf else -1
