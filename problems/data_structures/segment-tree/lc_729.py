import bisect
from typing import List, Tuple


# greedy + binary search
class MyCalendar:

    def __init__(self):
        self.arr: List[Tuple[int, int]] = []

    def book(self, startTime: int, endTime: int) -> bool:
        n = len(self.arr)
        idx = bisect.bisect_left(self.arr, (endTime, startTime))
        previous, next = False, False

        if idx == 0 or self.arr[idx - 1][0] <= startTime:
            previous = True
        if idx == n or self.arr[idx][1] >= endTime:
            next = True
        if previous and next:
            self.arr.insert(idx, (endTime, startTime))
            return True
        return False


# Your MyCalendar object will be instantiated and called as such:
# obj = MyCalendar()
# param_1 = obj.book(startTime,endTime)

obj = MyCalendar()
assert True == obj.book(37, 50)
assert False == obj.book(33, 50)
assert True == obj.book(4, 17)
assert False == obj.book(35, 48)
assert False == obj.book(8, 25)


# TODO: segment tree
# See https://www.geeksforgeeks.org/segment-tree-data-structure/
class MyCalendar:

    def __init__(self):
        pass

    def book(self, startTime: int, endTime: int) -> bool:
        pass


# Your MyCalendar object will be instantiated and called as such:
# obj = MyCalendar()
# param_1 = obj.book(startTime,endTime)

obj = MyCalendar()
assert True == obj.book(37, 50)
assert False == obj.book(33, 50)
assert True == obj.book(4, 17)
assert False == obj.book(35, 48)
assert False == obj.book(8, 25)
