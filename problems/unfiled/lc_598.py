from typing import List
from math import inf


class Solution:
    def maxCount(self, m: int, n: int, ops: List[List[int]]) -> int:
        cnt = len(ops)
        if cnt == 0: return m * n
        return min(ops[i][0] for i in range(cnt)) * min(ops[i][1] for i in range(cnt))
