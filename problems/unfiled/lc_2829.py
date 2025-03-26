class Solution:
    def minimumSum(self, n: int, k: int) -> int:
        if n > k // 2:
            return sum(range(1, k // 2 + 1)) + sum(range(k, k + n - k // 2))
        return sum(range(1, n + 1))


# fmt: off
class Solution:
    def minimumSum(self, n: int, k: int) -> int:
        if n > k // 2:
            return (1 + k // 2) * (k // 2) // 2 + (k + k + n - k // 2 - 1) * (n - k // 2) // 2
        return (1 + n) * n // 2
# fmt: on


# {1, 2}, {4, 5, 6}
n, k = 5, 4
ans = Solution().minimumSum(n, k)
print(ans)
assert ans == 18


n, k = 4, 7
ans = Solution().minimumSum(n, k)
print(ans)
assert ans == 13