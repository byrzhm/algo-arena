from collections import Counter
from heapq import heapify, heapreplace
from string import ascii_lowercase

"""

python 的 heap API:

heap = []            # creates an empty heap
heappush(heap, item) # pushes a new item on the heap
item = heappop(heap) # pops the smallest item from the heap
item = heap[0]       # smallest item on the heap without popping it
heapify(x)           # transforms list into a heap, in-place, in linear time
item = heapreplace(heap, item) # pops and returns smallest item, and adds
                               # new item; the heap size is unchanged


元组的默认比较函数:
在Python中，默认情况下，元组的比较是逐个比较其元素，并按照字典顺序进行比较。
具体来说，Python会按照元组中的第一个元素进行比较，如果它们相等，则继续比较第二个元素，以此类推，
直到找到不同的元素或者一个元组的元素用尽。

默认是最小堆，能否使用最大堆?
取负号实现最大堆

"""

class Solution:
    def minimizeStringValue(self, s: str) -> str:
        freq = Counter(s)
        h = [(freq[c], c) for c in ascii_lowercase]
        heapify(h)

        # print(freq)
        # print(h)

        t = []
        for _ in range(s.count('?')):
            f, c = h[0]
            t.append(c)
            heapreplace(h, (f + 1, c))  # 出现次数加一
        t.sort()  # 排序，因为要求字典序最小

        s = list(s)
        j = 0
        for i in range(len(s)):
            if s[i] == '?':
                s[i] = t[j]
                j += 1
                
        return ''.join(s)

if __name__ == '__main__':
    print(Solution().minimizeStringValue("abcdefg??"))
