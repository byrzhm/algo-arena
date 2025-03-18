from typing import List
from functools import cache
from math import sqrt


class Solution:
    def diagonalPrime(self, nums: List[List[int]]) -> int:
        @cache
        def isPrime(x: int) -> bool:
            if x == 1:
                return False
            for i in range(2, int(sqrt(x)) + 1):
                if x % i == 0:
                    return False
            return True

        n = len(nums)

        ans = 0
        for i in range(n):
            x, y = nums[i][i], nums[i][n - i - 1]
            if isPrime(x):
                ans = max(ans, x)
            if isPrime(y):
                ans = max(ans, y)
        return ans
