from typing import List
import copy
import heapq


class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        minHeap = copy.copy(nums)  # const: nums will not be modified
        # minHeap = nums  # nums will be modified
        heapq.heapify(minHeap)
        ans = 0
        while minHeap[0] < k:
            x1 = heapq.heappop(minHeap)
            x2 = heapq.heappop(minHeap)
            heapq.heappush(minHeap, x1 * 2 + x2)
            ans += 1
        return ans
