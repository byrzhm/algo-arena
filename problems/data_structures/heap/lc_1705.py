from typing import List
import heapq


# fmt: off
class Solution:
    def eatenApples(self, apples: List[int], days: List[int]) -> int:
        ans = 0
        minq = []
        n = len(apples)
        i = 0
        while i < n or minq:
            while minq and minq[0][0] <= i: # rot
                heapq.heappop(minq)
            if i < n and apples[i]:
                heapq.heappush(minq, [i + days[i], apples[i]])
            if minq:
                ans += 1
                minq[0][1] -= 1
                if minq[0][1] == 0:
                    heapq.heappop(minq)
            i += 1
        return ans
# fmt: on


apples = [1, 2, 3, 5, 2]
days = [3, 2, 1, 4, 2]
assert Solution().eatenApples(apples, days) == 7

apples = [3, 0, 0, 0, 0, 2]
days = [3, 0, 0, 0, 0, 2]
assert Solution().eatenApples(apples, days) == 5
