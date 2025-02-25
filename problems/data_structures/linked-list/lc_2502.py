from typing import Dict


class AllocNode:
    __slots__ = ["start", "end", "next"]

    def __init__(
        self,
        start: int = -1,
        end: int = -1,
        next: "AllocNode" = None,
    ):
        self.start: int = start
        self.end: int = end
        self.next: AllocNode = next

    def __repr__(self):
        string = ""
        x = self
        while x is not None:
            string += f"({x.start}, {x.end}) -> "
            x = x.next
        else:
            string += "None"
        return string


class Allocator:

    def __init__(self, n: int):
        self.freelist: AllocNode = AllocNode(next=AllocNode(start=0, end=n))
        self.alloc: Dict[int, AllocNode] = dict()

    def allocate(self, size: int, mID: int) -> int:
        x = self.freelist
        while x.next is not None and x.next.end - x.next.start < size:
            x = x.next

        if x.next is None:
            return -1

        if x.next.end - x.next.start == size:
            tmp = x.next
            x.next = tmp.next
            tmp.next = None
        else:
            x = x.next
            tmp = AllocNode(start=x.start, end=x.start + size)
            x.start = x.start + size

        if mID not in self.alloc:
            self.alloc[mID] = AllocNode()
        # print(f"insert {tmp} into alloc[{mID}] {self.alloc[mID]}")
        self.mergeInto(tmp, self.alloc[mID])
        # print(f"now alloc[{mID}] {self.alloc[mID]}")

        return tmp.start

    def freeMemory(self, mID: int) -> int:
        if mID not in self.alloc:
            return 0

        freed = 0
        head = self.alloc[mID]
        ptr = head.next
        while ptr is not None:
            freed += ptr.end - ptr.start
            head.next = ptr.next
            ptr.next = None
            # print(f"insert {ptr} into freelist {self.freelist}")
            self.mergeInto(ptr, self.freelist)
            # print(f"now freelist {self.freelist}")
            ptr = head.next
        return freed

    def mergeInto(self, node: AllocNode, head: AllocNode) -> None:
        # 向前合并与向后合并
        while head.next is not None and head.next.start < node.start:
            head = head.next
        # invariant: head.start < node.start <= head.next.start

        if head.end == node.start and (head.next is not None and head.next.start == node.end):
            head.end = head.next.end
            head.next = head.next.next
        elif head.end == node.start:
            head.end = node.end
        elif head.next is None or head.next.start != node.end:
            # head.start < head.end < node.start < node.end < head.next.start
            node.next = head.next
            head.next = node
        else:
            # elif head.next.start == node.end:
            head.next.start = node.start


# Your Allocator object will be instantiated and called as such:
# obj = Allocator(n)
# param_1 = obj.allocate(size,mID)
# param_2 = obj.freeMemory(mID)

# fmt: off
ops = ["Allocator","allocate","allocate","allocate","freeMemory","allocate","allocate","allocate","freeMemory","allocate","freeMemory"]
oprands = [[10],[1,1],[1,2],[1,3],[2],[3,4],[1,1],[1,1],[1],[10,2],[7]]
expected = [None, 0, 1, 2, 1, 3, 1, 6, 3, -1, 0]
# ops = ["Allocator","allocate","allocate","allocate","allocate","freeMemory","freeMemory","freeMemory","allocate","allocate","allocate","allocate","freeMemory","freeMemory","freeMemory","freeMemory","freeMemory","freeMemory","freeMemory","allocate","freeMemory","freeMemory","allocate","freeMemory","allocate","allocate","freeMemory","freeMemory","freeMemory","allocate","allocate","allocate","allocate","freeMemory","allocate","freeMemory","freeMemory","allocate","allocate","allocate","allocate","allocate","allocate","allocate","freeMemory","freeMemory","freeMemory","freeMemory"]
# oprands = [[50],[12,6],[28,16],[17,23],[50,23],[6],[10],[10],[16,8],[17,41],[44,27],[12,45],[33],[8],[16],[23],[23],[23],[29],[38,32],[29],[6],[40,11],[16],[22,33],[27,5],[3],[10],[29],[16,14],[46,47],[48,9],[36,17],[33],[14,24],[16],[8],[2,50],[31,36],[17,45],[46,31],[2,6],[16,2],[39,30],[33],[45],[30],[27]]
# expected = [None,0,12,-1,-1,12,0,0,-1,-1,-1,0,0,0,28,0,0,0,0,12,0,0,-1,0,-1,-1,0,0,0,-1,-1,-1,-1,0,-1,0,0,-1,-1,-1,-1,-1,-1,-1,0,12,0,0]
# fmt: on

obj = None
for i, op in enumerate(ops):
    if op == "Allocator":
        n = oprands[i][0]
        obj = Allocator(n)
    elif op == "allocate":
        size, mID = oprands[i]
        res = obj.allocate(size, mID)
        print(f"allocate size={size} mID={mID}")
        assert expected[i] == res, f"expect {expected[i]}, but get {res}"
    else:
        mID = oprands[i][0]
        res = obj.freeMemory(mID)
        print(f"freeMemory mID={mID}")
        assert expected[i] == res, f"expect {expected[i]}, but get {res}"
