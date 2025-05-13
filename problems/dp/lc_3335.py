from collections import defaultdict
from copy import copy

A = ord("a")
MOD = 1_000_000_007


class Solution:
    def lengthAfterTransformations(self, s: str, t: int) -> int:
        ans = len(s)
        arr = [0] * 26
        for c in s:
            x = ord(c) - A
            arr[x] = (arr[x] + 1) % MOD
        start, end = 0, 25

        for _ in range(t):
            ans = (ans + arr[end]) % MOD
            arr[start] = (arr[start] + arr[end]) % MOD
            start = (start - 1) % 26
            end = (end - 1) % 26

        return ans
