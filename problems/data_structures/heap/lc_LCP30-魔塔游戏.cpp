#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

/**
 *  小扣当前位于魔塔游戏第一层，共有 N 个房间，编号为 0 ~ N-1。
 * 每个房间的补血道具/怪物对于血量影响记于数组 nums，其中正数表示道具补血数值，
 * 即血量增加对应数值；负数表示怪物造成伤害值，即血量减少对应数值；0 表示房间对血量无影响。

 * 小扣初始血量为 1，且无上限。
 * 假定小扣原计划按房间编号升序访问所有房间补血/打怪，为保证血量始终为正值，
 * 小扣需对房间访问顺序进行调整，每次仅能将一个怪物房间（负数的房间）调整至访问顺序末尾。
 * 请返回小扣最少需要调整几次，才能顺利访问所有房间。若调整顺序也无法访问完全部房间，请返回 -1。
 */

class Solution
{
public:
  int magicTower(std::vector<int> &nums)
  {
    // 如果访问所有房间剩余的生命值不是正数，那么一定无法访问完全部房间
    // 可能溢出，所以使用 1LL
    int64_t hp = std::accumulate(nums.begin(), nums.end(), 1LL);
    if (hp <= 0)
      return -1;

    std::priority_queue<int> pq;  // 大根堆
    // std::deque<int> dq;
    int cnt = 0;
    hp      = 1;
    for (auto x : nums) {
      if (x < 0) {
        pq.emplace(-x);
      }
      hp += x;
      if (hp <= 0) {          // 反悔
        ++cnt;
        int most = pq.top();  // 反悔目前扣血最多的房间
        pq.pop();
        // dq.emplace_back(most);  // 将该房间的访问时间移到最后
        hp += most;
      }
    }

    // while (!dq.empty()) {
    //   int front = dq.front();
    //   dq.pop_front();
    //   sum -= front;
    //   if (sum <= 0) {
    //     ++cnt;
    //     sum += front;
    //     dq.emplace_back(front);
    //   }
    // }

    return cnt;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<int> nums{100, 100, 100, -250, -60, -140, -50, -50, 100, 150};
  std::cout << Solution().magicTower(nums) << '\n';

  return 0;
}