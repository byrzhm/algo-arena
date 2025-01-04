"""
See also fenwick solution: ../fenwick/lc_307*
In this solution, we use segment tree.
"""

from typing import List


# fmt: off
class NumArray:

    def __init__(self, nums: List[int]):
        n = len(nums)
        self.n = n
        self.seg = [0] * (n * 4)  # why n * 4 ?
                                  # if n is a power of 2, then it should be 2 * n - 1
                                  # if n is not a power of 2 and 2^t < n < 2^(t + 1),
                                  #   then it should be 2 * (2^(t + 1)) - 1 < 4 * n
        self.buildTree(nums, 0, 0, n - 1)

    def buildTree(self, nums: List[int], node: int, s: int, e: int):
        if s == e:
            self.seg[node] = nums[s]
            return
        mid = (s + e) >> 1  # s + (e - s) // 2
        left = node * 2 + 1
        right = node * 2 + 2
        self.buildTree(nums, left, s, mid)
        self.buildTree(nums, right, mid + 1, e)
        self.seg[node] = self.seg[left] + self.seg[right]

    def change(self, index: int, val: int, node: int, s: int, e: int):
        if s == e:
            self.seg[node] = val
            return
        mid = (s + e) >> 1
        left = 2 * node + 1
        right = 2 * node + 2
        if index <= mid:
            self.change(index, val, left, s, mid)
        else:
            self.change(index, val, right, mid + 1, e)
        self.seg[node] = self.seg[left] + self.seg[right]

    def range(self, l: int, r: int, node: int, s: int, e: int):
        if l == s and r == e:
            return self.seg[node]
        mid = (s + e) >> 1
        left = 2 * node + 1
        right = 2 * node + 2
        if r <= mid:
            return self.range(l, r, left, s, mid)
        if l > mid:
            return self.range(l, r, right, mid + 1, e)
        return self.range(l, mid, left, s, mid) + self.range(mid + 1, r, right, mid + 1, e)

    def update(self, index: int, val: int) -> None:
        self.change(index, val, 0, 0, self.n - 1)

    def sumRange(self, left: int, right: int) -> int:
        return self.range(left, right, 0, 0, self.n - 1)
# fmt: on


# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# obj.update(index,val)
# param_2 = obj.sumRange(left,right)
