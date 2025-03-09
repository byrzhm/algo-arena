from typing import List
from functools import cache
import bisect


# brute force
# O(n^2)
class Solution:
    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:

        @cache
        def solve(query: int) -> int:
            res = 0
            for price, beauty in items:
                if price <= query:
                    res = max(res, beauty)
            return res

        return [solve(q) for q in queries]


class Solution:
    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:
        ilen = len(items)
        items.sort(key=lambda item: item[0])
        prepares = [0] * (ilen + 1)  # prepares[i] <- max(beauty[0..i-1])
        for i, item in enumerate(items):
            _, beauty = item
            prepares[i + 1] = max(prepares[i], beauty)

        qlen = len(queries)
        ans = [0] * qlen

        for i, query in enumerate(queries):
            idx = bisect.bisect_right(items, query, key=lambda item: item[0])
            # price[idx] > query, price[idx - 1] <= query
            # if idx > 0: ans[i] <- prepares[idx]
            # else: ans[i] <- default 0
            # -/: prepares[0] is 0
            ans[i] = prepares[idx]

        return ans


items = [[1, 2], [3, 2], [2, 4], [5, 6], [3, 5]]
queries = [1, 2, 3, 4, 5, 6]

print(Solution().maximumBeauty(items, queries))
