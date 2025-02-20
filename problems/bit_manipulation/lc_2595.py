from typing import List


class Solution:
    def evenOddBit(self, n: int) -> List[int]:
        i = 0
        ans = [0] * 2
        while n > 0:
            ans[i] += n & 1
            n >>= 1
            i ^= 1
        return ans
