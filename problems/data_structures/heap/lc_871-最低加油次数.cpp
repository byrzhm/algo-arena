// #include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

/*

如何后悔？
- 到了一个站点后不选择直接加油，而是加入到后悔堆中, 
- 到了不得不加油的时候，再从反悔堆中选择油最多的一个站点进行加油

*/

class Solution
{
public:
  int minRefuelStops(int target, int startFuel, std::vector<std::vector<int>> &stations)
  {
    // std::sort(stations.begin(), stations.end(), [](const std::vector<int> &v1, const std::vector<int> &v2) {
    //   return v1.front() < v2.front();
    // });

    using MaxHeap = std::priority_queue<int>;
    MaxHeap heap;

    int currPos  = 0;                             ///< 当前的位置
    int currFuel = startFuel;                     ///< 当前的油量
    int count    = 0;                             ///< 加油次数

    for (auto &station : stations) {
      int position = station.front();             ///< 加油站的位置
      int fuel     = station.back();              ///< 加油站的油量
      int dist     = position - currPos;          ///< 当前位置到站点的距离
      while (!heap.empty() && dist > currFuel) {  // 油不够到该站点，从反悔堆里面加油
        ++count;                                  // 加油次数加1
        currFuel += heap.top();                   // 从堆顶的站点加油
        heap.pop();                               // 直接将该站点的油量全部加入
      }

      if (dist > currFuel) {                      // 还是无法到达该站点
        return -1;
      }

      heap.emplace(fuel);    // 当前站点加入反悔堆
      currFuel -= dist;      // 当前油量减少dist
      currPos   = position;  // 当前位置变为站点位置
    }

    // 考虑是否能到终点
    int dist = target - currPos;
    while (!heap.empty() && dist > currFuel) {
      ++count;
      currFuel += heap.top();
      heap.pop();
    }

    return dist > currFuel ? -1 : count;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
  int target    = 100;
  int startFuel = 10;
  std::vector<std::vector<int>> stations{
      {10, 60},
      {20, 30},
      {30, 30},
      {60, 40}
  };

  assert(Solution().minRefuelStops(target, startFuel, stations) == 2);

  return 0;
}