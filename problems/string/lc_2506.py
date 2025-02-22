from typing import List
from math import comb
from collections import defaultdict
from functools import reduce
from operator import or_


class Solution:
    def similarPairs(self, words: List[str]) -> int:
        hashtbl = defaultdict(int)
        for word in words:
            # word 排序去重
            hashtbl["".join(sorted(set(word)))] += 1
        ans = 0
        for k, v in hashtbl.items():
            ans += comb(v, 2)
        return ans


class Solution:
    def similarPairs(self, words: List[str]) -> int:
        ans = 0
        cnt = defaultdict(int)
        for word in words:
            # mask = 0
            # for c in s:
            #     mask |= 1 << (ord(c) - ord("a"))
            mask = reduce(or_, [1 << (ord(c) - ord("a")) for c in word], 0)
            ans += cnt[mask]
            cnt[mask] += 1
        return ans
