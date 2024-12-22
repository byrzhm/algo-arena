from functools import cache


class Solution:
    def getKth(self, lo: int, hi: int, k: int) -> int:
        # def get_power(x):
        #     power = 0
        #     while x != 1:
        #         if x % 2 == 0:
        #             x = x // 2
        #         else:
        #             x = 3 * x + 1
        #         power += 1
        #     return power

        # @cache
        # def get_power(x):
        #     if x == 1: return 0
        #     if x % 2 == 0: return get_power(x // 2) + 1
        #     else: return get_power(x * 3 + 1) + 1

        @cache
        def get_power(x):
            if x == 1:
                return 0
            if x % 2 == 0:
                return get_power(x // 2) + 1
            else:
                return get_power((x * 3 + 1) // 2) + 2

        arr = list(range(lo, hi + 1))
        arr.sort(key=lambda x: (get_power(x), x))  # stable sort, don't need tuple
        # arr.sort(key=get_power)
        return arr[k - 1]
