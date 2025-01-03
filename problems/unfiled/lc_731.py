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


class MyCalendarTwo:

    def __init__(self):
        pass

    def book(self, startTime: int, endTime: int) -> bool:
        pass


# TODO: 差分数组
class MyCalendarTwo:

    def __init__(self):
        pass

    def book(self, startTime: int, endTime: int) -> bool:
        pass


# TODO: 线段树
class MyCalendarTwo:

    def __init__(self):
        pass

    def book(self, startTime: int, endTime: int) -> bool:
        pass


# Your MyCalendarTwo object will be instantiated and called as such:
# obj = MyCalendarTwo()
# param_1 = obj.book(startTime,endTime)
