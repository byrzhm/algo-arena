#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

/*

给你一个数组 time ，其中 time[i] 表示第 i 辆公交车完成 一趟旅途 所需要花费的时间。

每辆公交车可以!连续!完成多趟旅途，也就是说，一辆公交车当前旅途完成后，可以!立马开始!下一趟旅途。
每辆公交车!独立!运行，也就是说可以同时有多辆公交车在运行且互不影响。

给你一个整数 totalTrips ，表示所有公交车总共需要完成的旅途数目。
请你返回完成 至少 totalTrips 趟旅途需要花费的!最少!时间。

*/

/*

! 为了使得花费的时间最少:
!   每辆公交必须不停歇地允许，在完成当前旅途完成后，必须立马开始下一趟旅途

! 单调性: 时间越长，完成的旅途会更多
* 根据时间二分，在指定时间内是否可以完成全部旅途

*/

class Solution
{
public:
  long long minimumTime(std::vector<int> &time, int totalTrips)
  {
    auto checkFn = [&](int64_t ddl) {
      int64_t finishTrips = std::accumulate(time.begin(), time.end(), 0LL, [&](int64_t res, int curr) {
        return res + ddl / curr;
      });
      return finishTrips >= totalTrips;
    };

    int64_t l = 0;
    int64_t r = *std::min_element(time.begin(), time.end()) * static_cast<int64_t>(totalTrips);

    while (l < r) {
      int64_t mid = (l + r) >> 1;
      if (checkFn(mid)) {  // 在规定时间内可以完成全部旅途
        r = mid;
      } else {             // 在规定时间内不可以完成全部旅途
        l = mid + 1;
      }
    }

    return l;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // std::vector<int> time{1, 2, 3};
  // int totalTrips = 5;

  std::vector<int> time{10000};
  int totalTrips = 10000000;

  std::cout << Solution().minimumTime(time, totalTrips) << '\n';

  return 0;
}