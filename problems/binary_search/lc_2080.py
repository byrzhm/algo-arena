from typing import List
from collections import defaultdict
from bisect import bisect_left, bisect_right


class RangeFreqQuery:

    def __init__(self, arr: List[int]):
        self.tbl = defaultdict(list)
        for i, x in enumerate(arr):
            self.tbl[x].append(i)

    def query(self, left: int, right: int, value: int) -> int:
        l = bisect_left(self.tbl[value], left)
        r = bisect_right(self.tbl[value], right)
        return r - l


obj = RangeFreqQuery([12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56])
ans = obj.query(1, 2, 4)
print(ans)
assert ans == 1
