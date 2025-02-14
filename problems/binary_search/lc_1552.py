from typing import List
from math import inf


class Solution:
    def maxDistance(self, position: List[int], m: int) -> int:
        position.sort()
        n = len(position)
        left, right = 1, position[-1]
        ans = -1

        def check(d: int) -> bool:
            cnt = 0
            prev = -inf
            for x in position:
                if x - prev >= d:
                    cnt = cnt + 1
                    prev = x
            return cnt >= m

        while left <= right:
            mid = (left + right) // 2
            if check(mid):
                ans = mid
                left = mid + 1
            else:
                right = mid - 1

        return ans
