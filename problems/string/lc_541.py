"""
[0, k - 1], [k, 2k - 1], ..., [xk, (x + 1)k - 1], [(x + 1)k, n]
"""


class Solution:
    def reverseStr(self, s: str, k: int) -> str:
        ans = ""
        n = len(s)
        for i in range(0, n, k):
            if i + k <= n:
                ans += s[i : i + k] if (i / k) % 2 != 0 else s[i : i + k][::-1]
            else:
                ans += s[i:n] if (i / k) % 2 != 0 else s[i:n][::-1]
        return ans


# In place solution
class Solution:
    def reverseStr(self, s: str, k: int) -> str:
        s = list(s)
        for i in range(0, len(s), 2 * k):
            s[i : i + k] = reversed(s[i : i + k])
        return "".join(s)
