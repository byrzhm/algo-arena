from typing import List

"""
https://leetcode.cn/problems/k-concatenation-maximum-sum/solutions/2764726/dpzuo-fa-zheng-que-xing-de-xiang-xi-zhen-kitt/
"""


class Solution:
    def kConcatenationMaxSum(self, arr: List[int], k: int) -> int:
        MOD = 1_000_000_007
        dp, s, a = 0, 0, 0
        t = 2 if k > 1 else 1
        for _ in range(t):
            for x in arr:
                s += x
                dp = max(x, dp + x)
                a = max(a, dp)
        s //= 2
        if s > 0:
            t = max(0, k - 2)
            a = (a + s * t) % MOD
        return a


arr = [1, -2, 1]
k = 5
assert Solution().kConcatenationMaxSum(arr, k) == 2
