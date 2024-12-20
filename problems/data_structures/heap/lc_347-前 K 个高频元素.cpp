#include <bits/stdc++.h>

class Solution
{
public:
  std::vector<int> topKFrequent(std::vector<int> &nums, int k)
  {
    int n = nums.size();
    std::vector<int> ans;
    std::vector<Node> nodes;
    std::unordered_map<int, int> freqMap;
    for (int num : nums) {
      freqMap[num]++;
    }

    nodes.reserve(freqMap.size());
    for (auto [num, freq] : freqMap) {
      nodes.emplace_back(num, freq);
    }

    std::make_heap(nodes.begin(), nodes.end());
    ans.reserve(k);
    while (k-- != 0) {
      std::pop_heap(nodes.begin(), nodes.end());
      ans.emplace_back(nodes.back().num);
      nodes.pop_back();
    }
    return ans;
  }

private:
  struct Node
  {
    int num  = 0;
    int freq = 0;

    bool operator<(const Node &other)
    {
      return this->freq < other.freq;
    }
  };
};