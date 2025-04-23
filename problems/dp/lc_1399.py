from collections import defaultdict
from functools import cache


class Solution:
    def countLargestGroup(self, n: int) -> int:
        def get_digits_sum(x: int) -> int:
            res = 0
            while x > 0:
                res += x % 10
                x //= 10
            return res

        tbl = defaultdict(int)

        for i in range(1, n + 1):
            tbl[get_digits_sum(i)] += 1

        maxval = -1
        cnt = 1
        for v in tbl.values():
            if v > maxval:
                cnt = 1
                maxval = v
            elif v == maxval:
                cnt += 1

        return cnt


# 数位DP
class Solution:
    def countLargestGroup(self, n: int) -> int:
        s = list(map(int, str(n)))  # 避免在 dfs 中频繁调用 int()
        m = len(s)

        @cache
        def dfs(i: int, left: int, limit_high: bool) -> int:
            if i == m:
                return 1 if left == 0 else 0
            hi = s[i] if limit_high else 9  # 当前数位至多填 hi
            res = 0
            for d in range(min(hi, left) + 1):  # 枚举当前数位填 d
                res += dfs(i + 1, left - d, limit_high and d == hi)
            return res

        max_cnt = ans = 0
        for target in range(1, m * 9 + 1):  # 枚举目标数位和
            cnt = dfs(0, target, True)
            if cnt > max_cnt:
                max_cnt = cnt
                ans = 1
            elif cnt == max_cnt:
                ans += 1
        return ans
