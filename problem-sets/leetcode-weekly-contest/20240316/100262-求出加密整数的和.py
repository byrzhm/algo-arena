from typing import List

class Solution:
    def sumOfEncryptedInt(self, nums: List[int]) -> int:
        # def f(x):
        #     s = str(x)
        #     return int(max(s) * len(s))

        def f(x):
            cnt, v = 0, 0
            while x:
                x, tmp = divmod(x, 10)
                cnt += 1
                v = max(v, tmp)
            # 最后相当于乘以 11...1 ，也就是 99...9 除以 9
            return v * (10 ** cnt - 1) // 9

        return sum(f(x) for x in nums)
