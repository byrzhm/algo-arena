class Solution:
    def canBeValid(self, s: str, locked: str) -> bool:
        n = len(s)
        if n % 2 != 0:
            return False

        mx = mn = 0
        for c, lck in zip(s, locked):
            if lck == "1":
                diff = 1 if c == "(" else -1
                mx += diff
                if mx < 0:
                    return False
                mn += diff
            else:
                mx += 1
                mn -= 1

            if mn < 0:  # 0 - 1 < 0
                mn = 1  # 因为之前是有效字符串

        return mn == 0


# s = "))()))"
# locked = "010100"
s = "())(()(()(())()())(())((())(()())((())))))(((((((())(()))))("
locked = "100011110110011011010111100111011101111110000101001101001111"
print(Solution().canBeValid(s, locked))
