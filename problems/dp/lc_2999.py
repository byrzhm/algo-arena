from functools import cache


# 数位DP
class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        high = list(map(int, str(finish)))  # 避免在 dfs 中频繁调用 int()
        n = len(high)
        low = list(map(int, str(start).zfill(n)))  # 补前导零，和 high 对齐
        diff = n - len(s)

        @cache
        def dfs(i: int, limit_low: bool, limit_high: bool) -> int:
            if i == n:
                return 1

            # 第 i 个数位可以从 lo 枚举到 hi
            # 如果对数位还有其它约束，应当只在下面的 for 循环做限制，不应修改 lo 或 hi
            lo = low[i] if limit_low else 0
            hi = high[i] if limit_high else 9

            res = 0
            if i < diff:  # 枚举这个数位填什么
                for d in range(lo, min(hi, limit) + 1):
                    res += dfs(i + 1, limit_low and d == lo, limit_high and d == hi)
            else:  # 这个数位只能填 s[i-diff]
                x = int(s[i - diff])
                if lo <= x <= hi:  # 题目保证 x <= limit，无需判断
                    res = dfs(i + 1, limit_low and x == lo, limit_high and x == hi)
            return res

        return dfs(0, True, True)


class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        start_ = str(start - 1)
        finish_ = str(finish)
        return self.calculate(finish_, s, limit) - self.calculate(start_, s, limit)

    def calculate(self, x: str, s: str, limit: int) -> int:
        if len(x) < len(s):
            return 0
        if len(x) == len(s):
            return 1 if x >= s else 0

        suffix = x[len(x) - len(s) :]
        count = 0
        pre_len = len(x) - len(s)

        for i in range(pre_len):
            if limit < int(x[i]):
                count += (limit + 1) ** (pre_len - i)
                return count
            count += int(x[i]) * (limit + 1) ** (pre_len - 1 - i)

        if suffix >= s:
            count += 1

        return count


start = 1
finish = 6000
limit = 4
s = "124"
print(Solution().numberOfPowerfulInt(start, finish, limit, s))

start = 15
finish = 215
limit = 6
s = "10"
print(Solution().numberOfPowerfulInt(start, finish, limit, s))

start = 1000
finish = 2000
limit = 4
s = "3000"
print(Solution().numberOfPowerfulInt(start, finish, limit, s))

start = 1300
finish = 1400
limit = 5
s = "245"
print(Solution().numberOfPowerfulInt(start, finish, limit, s))
