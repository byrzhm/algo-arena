class Solution:
    def minimumCost(self, s: str) -> int:
        n = len(s)
        prefix = [0] * n
        suffix = [0] * n

        for i in range(1, n):
            prefix[i] = prefix[i - 1] + (i if s[i] != s[i - 1] else 0)

        for i in range(n - 2, -1, -1):
            suffix[i] = suffix[i + 1] + ((n - i - 1) if s[i] != s[i + 1] else 0)

        return min(prefix[i] + suffix[i] for i in range(n))


class Solution:
    def minimumCost(self, s: str) -> int:
        n = len(s)
        ans = 0
        for i in range(1, n):
            if s[i] != s[i - 1]:
                ans += min(i, n - i)
        return ans
