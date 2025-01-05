from collections import defaultdict
from typing import List


# brute force
class MyCalendarTwo:

    def __init__(self):
        self.booked = []
        self.overlaps = []

    def book(self, startTime: int, endTime: int) -> bool:
        """
        [s...........e)
            [start..........end)

        [s........................e)
            [start..........end)

                    [s...........e)
        [start..........end)

        max(s, start) < min(e, end) <=> s < end and start < e
        """
        if any(s < endTime and startTime < e for s, e in self.overlaps):
            return False
        for s, e in self.booked:
            if s < endTime and startTime < e:
                self.overlaps.append((max(s, startTime), min(e, endTime)))
        self.booked.append((startTime, endTime))
        return True


# segment tree
# See https://www.geeksforgeeks.org/segment-tree-data-structure/
class MyCalendarTwo:

    def __init__(self):
        self.tree = defaultdict(int)
        self.lazy = defaultdict(int)

    def update(self, start: int, end: int, val: int, l: int, r: int, idx: int) -> None:
        if start > r or end < l:
            return
        if start <= l and r <= end:
            self.tree[idx] += val
            self.lazy[idx] += val
        else:
            mid = (l + r) >> 1
            self.update(start, end, val, l, mid, idx * 2)
            self.update(start, end, val, mid + 1, r, idx * 2 + 1)
            self.tree[idx] = self.lazy[idx] + max(
                self.tree[idx * 2], self.tree[idx * 2 + 1]
            )

    def book(self, startTime: int, endTime: int) -> bool:
        self.update(startTime, endTime - 1, 1, 0, 10**9, 1)
        if self.tree[1] > 2:
            self.update(startTime, endTime - 1, -1, 0, 10**9, 1)
            return False
        return True
