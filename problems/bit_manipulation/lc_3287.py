from typing import List
from functools import reduce
from operator import or_


# fmt: off
class Solution:
    def maxValue(self, nums: List[int], k: int) -> int:
        k0 = k
        k = min(k, 7)
        n = len(nums)
        U = 1 << max(nums).bit_length()
        minL = [n + 1] * U
        maxR = [-1] * U
        cnt = [0] * U
        for i in range(n):
            for j in range(U):
                if j == (j | nums[i]):
                    cnt[j] += 1
                    if cnt[j] == k0:
                        minL[j] = i
        cnt = [0] * U
        for i in range(n - 1, -1, -1):
            for j in range(U):
                if j == (j | nums[i]):
                    cnt[j] += 1
                    if cnt[j] == k0:
                        maxR[j] = i

        suf = [None] * (n - k0 + 1)
        f = [set() for _ in range(k + 1)]
        f[0].add(0)
        for i in range(n - 1, k0 - 1, -1):
            v = nums[i]
            for j in range(min(k - 1, n - 1 - i), -1, -1):
                f[j + 1].update(x | v for x in f[j])
            if i <= n - k0:
                suf[i] = f[k].copy()

        mx = reduce(or_, nums)
        ans = 0
        pre = [set() for _ in range(k + 1)]
        pre[0].add(0)
        for i, v in enumerate(nums[:-k0]):
            for j in range(min(k - 1, i), -1, -1):
                pre[j + 1].update(x | v for x in pre[j])
            if i < k0 - 1:
                continue
            ans = max(ans, max(x ^ y for x in pre[k] for y in suf[i + 1]
                               if minL[x] <= i and maxR[y] >= i + 1))
            if ans == mx:
                return ans
        return ans
# fmt: on
