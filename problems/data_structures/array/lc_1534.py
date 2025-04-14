from typing import List


class Solution:
    def countGoodTriplets(self, arr: List[int], a: int, b: int, c: int) -> int:
        n = len(arr)
        ans = 0
        for i in range(n - 2):
            for j in range(i + 1, n - 1):
                for k in range(j + 1, n):
                    if (
                        abs(arr[i] - arr[j]) <= a
                        and abs(arr[j] - arr[k]) <= b
                        and abs(arr[i] - arr[k]) <= c
                    ):
                        ans += 1
        return ans


class Solution:
    def countGoodTriplets(self, arr: List[int], a: int, b: int, c: int) -> int:
        idx = sorted(range(len(arr)), key=lambda i: arr[i])

        ans = 0
        for j in idx:
            y = arr[j]
            left = [arr[i] for i in idx if i < j and abs(arr[i] - y) <= a]
            right = [arr[k] for k in idx if k > j and abs(arr[k] - y) <= b]

            k1 = k2 = 0
            for x in left:
                while k2 < len(right) and right[k2] <= x + c:
                    k2 += 1
                while k1 < len(right) and right[k1] < x - c:
                    k1 += 1
                ans += k2 - k1
        return ans
