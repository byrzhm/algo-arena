#include <bits/stdc++.h>

namespace bruteforce {

class Solution {
 public:
  double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
    int m = nums1.size();
    int n = nums2.size();
    int tot_len = m + n;
    int idx1 = 0;
    int idx2 = 0;
    double median = 0.0;
    int begin = (tot_len - 1) / 2;
    int count = 2 - tot_len % 2;
    for (int i = 0; i < tot_len; ++i) {
      int tmp;
      if (idx1 < m && idx2 < n) {
        if (nums1[idx1] < nums2[idx2]) {
          tmp = nums1[idx1];
          ++idx1;
        } else {
          tmp = nums2[idx2];
          ++idx2;
        }
      } else if (idx1 < m) {
        tmp = nums1[idx1];
        ++idx1;
      } else if (idx2 < n) {
        tmp = nums2[idx2];
        ++idx2;
      }

      // std::cout << tmp << std::endl;

      if (i >= begin) {
        median += tmp;
      }

      if (i >= begin + count - 1) {
        break;
      }
    }
    return median / count;
  }
};

}  // namespace bruteforce

namespace binary_search {

/**
 * [Binary Search : Median of two sorted arrays of different sizes.](https://www.youtube.com/watch?v=LPFhl65R7ww)
 *
 */
class Solution {
 public:
  double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
    std::vector<int> *longNums = nullptr;
    std::vector<int> *shortNums = nullptr;
    if (nums1.size() > nums2.size()) {
      longNums = &nums1;
      shortNums = &nums2;
    } else {
      longNums = &nums2;
      shortNums = &nums1;
    }

    int shortLen = shortNums->size();
    int longLen = longNums->size();
    int total_len = shortLen + longLen;
    int total_half = (total_len + 1) >> 1;  // 向上取整, 总长为奇数时, 中位数在左边

    int first = 0;
    int last = shortLen;

    while (first <= last) {  // 等号成立时, 说明 shortNums 划分为"空"和"自身"两部分
      int partitionS = (first + last) >> 1;
      int partitionL = total_half - partitionS;

      int maxLeftS = (partitionS == 0) ? std::numeric_limits<int>::min() : (*shortNums)[partitionS - 1];
      int minRightS = (partitionS == shortLen) ? std::numeric_limits<int>::max() : (*shortNums)[partitionS];

      int maxLeftL = (partitionL == 0) ? std::numeric_limits<int>::min() : (*longNums)[partitionL - 1];
      int minRightL = (partitionL == longLen) ? std::numeric_limits<int>::max() : (*longNums)[partitionL];

      if (maxLeftL <= minRightS && maxLeftS <= minRightL) {
        if (total_len % 2 == 1) {
          return static_cast<double>(std::max(maxLeftL, maxLeftS));
        }
        return static_cast<double>(std::max(maxLeftL, maxLeftS) + std::min(minRightL, minRightS)) / 2;
      }

      if (maxLeftL > minRightS) {
        first = partitionS + 1;
      } else {
        last = partitionS;
      }
    }

    return -1;
  }
};

}  // namespace binary_search

// 使用 iterator 会比 [] 快一点
namespace iterator_binary_search {

class Solution {
 public:
  double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
    std::vector<int> *longNums = nullptr;
    std::vector<int> *shortNums = nullptr;
    if (nums1.size() > nums2.size()) {
      longNums = &nums1;
      shortNums = &nums2;
    } else {
      longNums = &nums2;
      shortNums = &nums1;
    }

    int len = shortNums->size();
    int total_len = shortNums->size() + longNums->size();
    int total_half = (total_len + 1) >> 1;  // 向上取整, 总长为奇数时, 中位数在左边

    auto firstS = shortNums->begin();

    while (len >= 0) {  // 等号成立时, 说明 shortNums 划分为"空"和"自身"两部分
      int half = len >> 1;
      auto partitionS = firstS;
      std::advance(partitionS, half);
      int off = total_half - (partitionS - shortNums->begin());
      auto partitionL = longNums->begin();
      std::advance(partitionL, off);

      int maxLeftS = (partitionS == shortNums->begin()) ? std::numeric_limits<int>::min() : *(partitionS - 1);
      int minRightS = (partitionS == shortNums->end()) ? std::numeric_limits<int>::max() : *partitionS;

      int maxLeftL = (partitionL == longNums->begin()) ? std::numeric_limits<int>::min() : *(partitionL - 1);
      int minRightL = (partitionL == longNums->end()) ? std::numeric_limits<int>::max() : *partitionL;

      if (maxLeftL <= minRightS && maxLeftS <= minRightL) {
        if (total_len % 2 == 1) {
          return static_cast<double>(std::max(maxLeftL, maxLeftS));
        }
        return static_cast<double>(std::max(maxLeftL, maxLeftS) + std::min(minRightL, minRightS)) / 2;
      }

      if (maxLeftL > minRightS) {
        firstS = partitionS;
        ++firstS;
        len = len - half - 1;
      } else {
        len = half;
      }
    }

    return -1;
  }
};

}  // namespace iterator_binary_search

int main() {
  {
    std::vector<int> nums1 = {1, 2};
    std::vector<int> nums2 = {3, 4};
    std::cout << binary_search::Solution().findMedianSortedArrays(nums1, nums2) << std::endl;
  }
  {
    std::vector<int> nums1 = {3, 4};
    std::vector<int> nums2 = {1, 2};
    std::cout << binary_search::Solution().findMedianSortedArrays(nums1, nums2) << std::endl;
  }
}