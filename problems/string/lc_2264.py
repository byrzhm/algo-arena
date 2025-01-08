class Solution:
    def largestGoodInteger(self, num: str) -> str:
        ans = ""
        n = len(num)
        for i in range(n - 2):
            if ans < num[i] == num[i + 1] == num[i + 2]:
                ans = num[i]
        return ans * 3
