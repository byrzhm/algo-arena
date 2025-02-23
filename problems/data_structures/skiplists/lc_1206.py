from typing import List
from random import random

MAX_LEVEL = 32
P_FACTOR = 0.5


class SkiplistNode:
    __slots__ = ["val", "forward"]

    def __init__(self, val, max_level: int = MAX_LEVEL):
        self.val = val
        self.forward: List[SkiplistNode] = [None] * max_level


class Skiplist:

    def __init__(self):
        self.head = SkiplistNode(-1)
        self.level = 0

    def search(self, target: int) -> bool:
        x = self.head
        # loop invariant: x.val < target and x is not None
        for i in range(self.level - 1, -1, -1):
            while x.forward[i] and x.forward[i].val < target:
                x = x.forward[i]
        # x.val < target <= x.forward[0].val, if x.forward[0] is not None
        x = x.forward[0]
        return x is not None and x.val == target

    def add(self, num: int) -> None:
        update: List[SkiplistNode] = [None] * MAX_LEVEL
        x = self.head
        for i in range(self.level - 1, -1, -1):
            while x.forward[i] and x.forward[i].val < num:
                x = x.forward[i]
            # x.val < num <= x.forward[i].val, if x.forward[i] is not None
            update[i] = x
        x = x.forward[0]
        # 如果不允许重复, 下面两行需要加上
        # if x is not None and x.val == num:
        #     return

        lvl = self.random_level()
        if lvl > self.level:
            for i in range(self.level, lvl):
                update[i] = self.head
            self.level = lvl
        new_node = SkiplistNode(num, lvl)
        for i in range(lvl):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def erase(self, num: int) -> bool:
        update: List[SkiplistNode] = [None] * MAX_LEVEL

        x = self.head
        for i in range(self.level - 1, -1, -1):
            while x.forward[i] and x.forward[i].val < num:
                x = x.forward[i]
            # x.val < num <= x.forward[i].val, if x.forward[i] is not None
            update[i] = x

        x = x.forward[0]

        if x is None or x.val != num:
            return False

        for i in range(self.level):
            if update[i].forward[i] != x:
                break
            update[i].forward[i] = x.forward[i]
        while self.level > 0 and self.head.forward[self.level - 1] is None:
            self.level -= 1
        return True

    def random_level(self) -> int:
        lvl = 1
        # random() that returns a random value in [0...1)
        while random() < P_FACTOR and lvl < MAX_LEVEL:
            lvl += 1
        return lvl


# fmt: off
opcodes: List[str] = [ "Skiplist", "add", "add", "add", "add", "add", "add", "add", "add", "add", "erase", "search", "add", "erase", "erase", "erase", "add", "search", "search", "search", "erase", "search", "add", "add", "add", "erase", "search", "add", "search", "erase", "search", "search", "erase", "erase", "add", "erase", "search", "erase", "erase", "search", "add", "add", "erase", "erase", "erase", "add", "erase", "add", "erase", "erase", "add", "add", "add", "search", "search", "add", "erase", "search", "add", "add", "search", "add", "search", "erase", "erase", "search", "search", "erase", "search", "add", "erase", "search", "erase", "search", "erase", "erase", "search", "search", "add", "add", "add", "add", "search", "search", "search", "search", "search", "search", "search", "search", "search", ]
oprands: List[List[int]] = [ [], [16], [5], [14], [13], [0], [3], [12], [9], [12], [3], [6], [7], [0], [1], [10], [5], [12], [7], [16], [7], [0], [9], [16], [3], [2], [17], [2], [17], [0], [9], [14], [1], [6], [1], [16], [9], [10], [9], [2], [3], [16], [15], [12], [7], [4], [3], [2], [1], [14], [13], [12], [3], [6], [17], [2], [3], [14], [11], [0], [13], [2], [1], [10], [17], [0], [5], [8], [9], [8], [11], [10], [11], [10], [9], [8], [15], [14], [1], [6], [17], [16], [13], [4], [5], [4], [17], [16], [7], [14], [1], ]
expected: List[bool] = [ None, None, None, None, None, None, None, None, None, None, True, False, None, True, False, False, None, True, True, True, True, False, None, None, None, False, False, None, False, False, True, True, False, False, None, True, True, False, True, True, None, None, False, True, False, None, True, None, True, True, None, None, None, False, False, None, True, False, None, None, True, None, False, False, False, True, True, False, True, None, True, False, False, False, True, True, False, False, None, None, None, None, True, True, True, True, True, True, False, False, True, ]
# fmt: on


obj = None

for i, opcode in enumerate(opcodes):
    if opcode == "Skiplist":
        obj = Skiplist()
        continue

    oprand = oprands[i][0]
    print(f"{i}: {opcode} {oprand}")
    if opcode == "add":
        obj.add(oprand)
    elif opcode == "search":
        assert (
            obj.search(oprand) == expected[i]
        ), f"{i}: search {oprand}, expect {expected[i]}"
    elif opcode == "erase":
        assert (
            obj.erase(oprand) == expected[i]
        ), f"{i}: erase {oprand}, expect {expected[i]}"
