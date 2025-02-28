from typing import List, Dict, Tuple
from sortedcontainers import SortedList
from collections import defaultdict
import heapq

"""
balanced tree
"""


# fmt: off
class FoodRatings:

    def __init__(self, foods: List[str], cuisines: List[str], ratings: List[int]):
        self.info: Dict[str, List[int, str]] = {}  # food -> [rating, cuisine]
        self.tbl: Dict[str, SortedList] = defaultdict(SortedList)  # cuisine -> SortedList([(rating, food)])

        for food, cuisine, rating in zip(foods, cuisines, ratings):
            self.info[food] = [rating, cuisine]
            self.tbl[cuisine].add((-rating, food))

    def changeRating(self, food: str, newRating: int) -> None:
        oldRating, cuisine = self.info[food]
        self.info[food][0] = newRating
        # self.tbl[cuisine].discard((-oldRating, food)) # when value not in list, do nothing
        self.tbl[cuisine].remove((-oldRating, food)) # when value not in list, raise ValueError
        self.tbl[cuisine].add((-newRating, food))

    def highestRated(self, cuisine: str) -> str:
        return self.tbl[cuisine][0][1]
# fmt:on


"""
Lazy Heap
"""


# fmt: off
class FoodRatings:

    def __init__(self, foods: List[str], cuisines: List[str], ratings: List[int]):
        self.lazyHeap: Dict[str, List[Tuple[int, str]]] = defaultdict(list) # rating, food
        self.info: Dict[str, List[int, str]] = {} # food -> rating, cuisine
        for food, cuisine, rating in zip(foods, cuisines, ratings):
            heapq.heappush(self.lazyHeap[cuisine], (-rating, food))
            self.info[food] = [rating, cuisine]

    def changeRating(self, food: str, newRating: int) -> None:
        _, cuisine = self.info[food]
        self.info[food][0] = newRating
        heapq.heappush(self.lazyHeap[cuisine], (-newRating, food))

    def highestRated(self, cuisine: str) -> str:
        while True:
            rating, food = self.lazyHeap[cuisine][0]
            latestRating, _ = self.info[food]
            if latestRating == abs(rating):
                return food
            heapq.heappop(self.lazyHeap[cuisine])
# fmt: on
