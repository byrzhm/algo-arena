from typing import List


"""
Wrong Solution:
    Out of memory limit
"""

f = [[0] * 101 for _ in range(100_000 + 1)]  # Initialize the f array with 0s
f[0][0] = 1  # Base case: C(0, 0) = 1

# Compute all combinations using Pascal's Triangle
for i in range(1, 100_000 + 1):
    f[i][0] = 1  # C(i, 0) is always 1
    for l in range(1, 101):
        f[i][l] = f[i - 1][l - 1] + f[i - 1][l]


class Solution:
    def minMaxSums(self, nums: List[int], k: int) -> int:
        MOD = 1_000_000_007
        n = len(nums)
        nums.sort()
        ans = 0
        for l in range(1, k + 1):
            for s in range(n - l + 1):
                ans = (ans + nums[s] * f[n - s - 1][l - 1]) % MOD
            for e in range(n - 1, l - 2, -1):
                ans = (ans + nums[e] * f[e][l - 1]) % MOD
        return ans
