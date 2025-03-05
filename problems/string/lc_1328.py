class Solution:
    def breakPalindrome(self, palindrome: str) -> str:
        palindrome = list(palindrome)
        n = len(palindrome)
        if n == 1:
            return ""

        lastb = True
        l, r = 0, n - 1
        while l < r:
            if palindrome[l] != "a":
                lastb = False
                palindrome[l] = "a"
                break
            l, r = l + 1, r - 1
        if lastb:
            palindrome[-1] = "b"
        return "".join(palindrome)


class Solution:
    def breakPalindrome(self, palindrome: str) -> str:
        palindrome = list(palindrome)
        n = len(palindrome)
        if n == 1:
            return ""

        for i in range(n // 2):  # 5 -> 0, 1; 4 -> 0, 1
            if palindrome[i] != "a":
                palindrome[i] = "a"
                return "".join(palindrome)
        palindrome[-1] = "b"
        return "".join(palindrome)
