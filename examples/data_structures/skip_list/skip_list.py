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
        if x is not None and x.val == num:
            return

        lvl = self.random_level()
        if lvl > self.level:
            for i in range(self.level + 1, lvl):
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

    # TODO: visualize skiplists
    # def display(self):
    #     from graphviz import Digraph

    #     def get_all_nodes():
    #         nodes = []
    #         current = self.head.forward[0]
    #         while current:
    #             nodes.append(current)
    #             current = current.forward[0]
    #         return nodes

    #     nodes = [self.head] + get_all_nodes()  # 包含头节点

    #     dot = Digraph(comment="SkipList", format="png")
    #     dot.attr(rankdir="LR", splines="polyline")  # 从左到右布局，使用直线

    #     for node in nodes:
    #         # 创建HTML表格
    #         label = '''<<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0">'''
    #         # 添加各层指针，从最高层到层0
    #         for level in range(self.level - 1, -1, -1):
    #             if level < len(node.forward):
    #                 forward_node = node.forward[level]
    #                 label += f'<TR><TD PORT="layer{level}">→ {forward_node.val if forward_node else ""}</TD></TR>'
    #             else:
    #                 # 该节点无此层，生成空行保持对齐
    #                 label += f'<TR><TD PORT="layer{level}"></TD></TR>'
    #         # 添加节点值行
    #         value = node.val if node.val is not None else "H"
    #         label += f'<TR><TD>{value}</TD></TR></TABLE>>'
    #         dot.node(str(id(node)), label=label, shape='plaintext')

    #         # 添加各层的边
    #         for level in range(len(node.forward)):
    #             forward_node = node.forward[level]
    #             if forward_node:
    #                 dot.edge(f"{id(node)}:layer{level}", f"{id(forward_node)}:layer{level}")

    #     # 按层0顺序排列节点（包括头节点）
    #     with dot.subgraph() as s:
    #         s.attr(rank='same')
    #         for node in nodes:
    #             s.node(str(id(node)))

    #     dot = obj.display()
    #     dot.render(f"skiplist-{i}", view=False)
    #     return dot
