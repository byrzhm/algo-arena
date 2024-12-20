#include <bits/stdc++.h>

class Solution {
 public:
  int sumIndicesWithKSetBits(std::vector<int> &nums, int k) {
    int sum = 0;
    int size = nums.size();
    for (int i = 0; i < size; ++i)
      if (numberOfBitSet(i) == k) sum = sum + nums[i];
    return sum;
  }

  int numberOfBitSet(int i) {
    std::bitset<32> bits(i);
    return bits.count();
  }
  // int numberOfBitSet(int i) {
  //   int count = 0;
  //   while (i > 0) {
  //     count = count + (i & 1);
  //     i = i >> 1;
  //   }
  //   return count;
  // }
};