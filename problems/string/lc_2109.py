from typing import List
from itertools import pairwise


class Solution:
    def addSpaces(self, s: str, spaces: List[int]) -> str:
        strings = []
        spaces.insert(0, 0)
        spaces.append(len(s))

        for start, end in pairwise(spaces):
            strings.append(s[start:end])

        return " ".join(strings)
