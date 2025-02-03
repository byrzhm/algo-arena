class Solution:
    def validPalindrome(self, s: str) -> bool:
        n = len(s)
        l, r = 0, n - 1

        def check(i: int, j: int) -> bool:
            while i < j:
                if s[i] != s[j]:
                    return False
                i += 1
                j -= 1
            return True

        while l < r and s[l] == s[r]:
            l += 1
            r -= 1

        if l >= r:
            return True

        # abcca -> acca
        # i-1 [ i i+1 ... j-1 j ] j+1   <- j > i + 2
        # i-1 [ i i+1 j ] j+1           <- j == i + 2
        # i-1 [ i j ] j+1               <- j == i + 1
        if s[l + 1] == s[r] and check(l + 1, r):  # delete l
            return True

        if s[l] == s[r - 1] and check(l, r - 1):  # delete r
            return True

        return False
