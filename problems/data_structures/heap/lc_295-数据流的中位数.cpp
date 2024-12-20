#include <bits/stdc++.h>

class MedianFinder
{
public:
  MedianFinder() = default;

  void addNum(int num)
  {
    // 上面的最小堆数量不会少于下面的最大堆
    if (topHeap.empty()) {
      topHeap.push(num);
      return;
    }

    if (topHeap.size() > downHeap.size()) {  // 下面的最大堆数量少些
      if (num <= topHeap.top()) {            // 新添加的数比上面的数都小, 可以直接放入下面
        downHeap.push(num);
      } else {                               // 新添加的数不比上面的数都小, 也就是说比下面的数都大, 最好放在上面
        downHeap.push(topHeap.top());        // 把上面最小的数借给下面, 然后将新数放在上面
        topHeap.pop();                       // 这样上面的数量没变, 下面的数量加1
        topHeap.push(num);
      }
    } else {                                 // 上面的最小堆数量少些
      if (num >= downHeap.top()) {           // 新添加的数比下面的数都大, 可以直接放入上面
        topHeap.push(num);
      } else {                               // 新添加的数不比下面的数都大, 也就是说比上面的数都小, 最好放在下面
        topHeap.push(downHeap.top());        // 把下面最大的数借给上面, 然后把新数放在下面
        downHeap.pop();                      // 这样下面的数量没变, 上面的数量加1
        downHeap.push(num);
      }
    }
  }

  double findMedian()
  {
    // 当总数量为奇数时, 中位数为上面最小堆的堆顶元素
    // 其他情况下, 为上下两个堆顶的均值
    if ((topHeap.size() + downHeap.size()) % 2 == 1)
      return topHeap.top();

    if (topHeap.empty() && downHeap.empty())
      throw std::runtime_error("out of bound");

    return static_cast<double>(topHeap.top() + downHeap.top()) / 2;
  }

private:
  std::priority_queue<int, std::vector<int>, std::greater<>> topHeap;  // top, min heap
  std::priority_queue<int, std::vector<int>, std::less<>> downHeap;    // down, max heap
};



/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main()
{
  auto obj = std::make_unique<MedianFinder>();
  obj->addNum(1);
  obj->addNum(2);
  std::cout << obj->findMedian() << '\n';
  obj->addNum(3);
  std::cout << obj->findMedian() << '\n';
}