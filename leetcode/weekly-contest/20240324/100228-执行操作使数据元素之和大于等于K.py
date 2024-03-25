from cmath import sqrt
from math import ceil

"""
枚举
"""

class Solution:
    def minOperations(self, k: int) -> int:
        return min(m - 1 + (k - 1) // m for m in range(1, k + 1))

"""
二分
"""

class Solution:
    def minOperations(self, k: int) -> int:
        if k == 1:
            return 0

        def check(target: int) -> bool:
            for i in range(0, target + 1):
                val = 1 + i
                sum = val * (target - i + 1)
                if sum >= k: return True
            return False

        left, right = 1, k - 1
        while left < right:
            middle = (left + right) // 2
            if check(middle):
                right = middle
            else:
                left = middle + 1

        return left

"""
数学
"""
class Solution:
    def minOperations(self, k: int) -> int:
       return ceil(2*sqrt(k)-2)
 