class Solution:
    def minSwaps(self, s: str) -> int:
        s = list(s)
        n = len(s)
        j = n - 1
        ans, cnt = 0, 0
        for i, c in enumerate(s):
            if c == "[":
                cnt += 1
            else:  # c == ']'
                if cnt > 0:
                    cnt -= 1
                else:
                    while j > i and s[j] != "[":
                        j -= 1
                    s[i], s[j] = s[j], s[i]
                    cnt += 1
                    ans += 1
        return ans
