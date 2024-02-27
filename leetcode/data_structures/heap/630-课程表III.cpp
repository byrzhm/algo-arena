#include <functional>
#include <iostream>
#include <queue>
#include <vector>

/*

这里有 n 门不同的在线课程，按从 1 到 n 编号。
给你一个数组 courses ，其中 courses[i] = [durationi, lastDayi] 
表示第 i 门课将会 持续 上 durationi 天课，并且必须在不晚于 lastDayi 的时候完成。

你的学期从第 1 天开始。且不能同时修读两门及两门以上的课程。

返回你最多可以修读的课程数目。

*/

/*


*/

class Solution
{
public:
  int scheduleCourse(std::vector<std::vector<int>> &courses)
  {
    std::sort(courses.begin(), courses.end(), [](std::vector<int> &l, std::vector<int> &r) {
      return l.back() < r.back();
    });

    using MaxHeap = std::priority_queue<int, std::vector<int>, std::less<>>;

    MaxHeap heap;

    int takeCnt   = 0;
    int courseNum = courses.size();
    int day       = 0;
    int idx       = 0;
    int freeDay   = 0;

    while (idx < courseNum) {
      int duration = courses[idx].front();
      int lastDay  = courses[idx].back();

      if (day != lastDay) {  // 没到某门课程的最后一天
        ++freeDay;           // 这一天空闲
        ++day;               // 进入下一天
        continue;
      }

      // 到了某门课程的最后一天

      if (duration > lastDay) {  // 该课程 duration > lastDay
        ++idx;                   // 考虑下一门课程
        continue;
      }

      if (duration > freeDay) {                       // 空闲时间不够学习该门课程，尝试反悔
        if (heap.empty() || heap.top() < duration) {  // 无法反悔，或反悔会使得结果更糟
          ++idx;                                      // 考虑下一门课程
          continue;
        }

        --takeCnt;  // 退课
        freeDay += heap.top();
        heap.pop();
      }
      ++takeCnt;  // 选课
      freeDay -= duration;
      heap.push(duration);
      ++idx;      // 考虑下一门课程
    }

    return takeCnt;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // std::vector<std::vector<int>> courses{
  //     {100, 200},
  //     {200, 1300},
  //     {1000, 1250},
  //     {2000, 3200}
  // };

  // [[3,14],[6,18],[10,16],[3,4],[4,5],[7,15],[2,9],[1,6],[10,13],[5,16]]
  // sorted 👇
  // [[3,4],[4,5],[1,6],[2,9],[10,13],[3,14],[7,15],[10,16],[5,16],[6,18]]
  // * [3,4] freeDay=4 > duration=3
  // ! [4,5] freeDay=2 < duration=4, heaptop=3 不后悔
  // * [1,6] freeDay=3 > duration=1
  // * [2,9] freeDay=5 > duration=2
  // ! [10,13] freeDay=7 < duration=10, heaptop=3 不后悔
  // * [3,14] freeDay=8 > duration=3
  // ! [7, 15] freeDay=6 < duration=7, heaptop=3 不后悔
  // ! [10,16] freeDay=7 < duration=10, heaptop=3 不后悔
  // * [5,16] freeDay=7 > duration=5
  // ! [6,18] freeDay=4 < duration=6, heaptop=5 不后悔
  // ? 最后选了5门课


  std::vector<std::vector<int>> courses{
      {3, 14},
      {6, 18},
      {10, 16},
      {3, 4},
      {4, 5},
      {7, 15},
      {2, 9},
      {1, 6},
      {10, 13},
      {5, 16}
  };

  std::cout << Solution().scheduleCourse(courses) << '\n';

  return 0;
}