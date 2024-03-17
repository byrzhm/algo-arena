from collections import Counter
from math import inf

# class Solution:
#     def minimumDeletions(self, word: str, k: int) -> int:
#         nums = Counter(word).values()
#         def calc(v):
#             result = 0
#             for x in nums:
#                 if x < v: result += x
#                 elif x > v + k: result += x - v - k
#             return result
#         return min(calc(i) for i in range(len(word) + 1))

class Solution:
    def minimumDeletions(self, word: str, k: int) -> int:
        nums = Counter(word).values()
        def calc(v):
            result = 0
            for x in nums:
                if x < v: result += x
                elif x > v + k: result += x - v - k
            return result
        ans = inf
        for x in nums:
            for v in [max(0, x - k), x]:
                ans = min(ans, calc(v))
        return ans

        # vals = set()
        # for x in nums:
        #     vals.add(x)

        # ans = inf
        # for val in vals:
        #     ans = min(ans, calc(val))
        # return ans
