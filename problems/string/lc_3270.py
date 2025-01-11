class Solution:
    def generateKey(self, num1: int, num2: int, num3: int) -> int:
        strings = [f"{x:04d}" for x in [num1, num2, num3]]
        return int(''.join(min(map(lambda string: string[i], strings)) for i in range(4)))


num1, num2, num3 = 1, 10, 1000
print(Solution().generateKey(num1, num2, num3))
