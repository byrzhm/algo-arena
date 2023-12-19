/**
 * 1007 Maximum Subsequence Sum
 */
#include <bits/stdc++.h>

std::tuple<int, int, int> SolveMSS(const std::vector<int> &nums) {
  /**
   * 最大子序和
   * mss[n] 表示以 nums[n] 结尾的子序列的最大子序和
   */
  std::vector<int> mss(nums.begin(), nums.end());
  int maxsum = mss[0];
  int start = 0;
  int end = 0;
  int p = 0;

  /**
   * mss[n] = max(mss[n-1] + a[n], a[n])
   */
  for (size_t i = 1; i < nums.size(); i++) {
    if (mss[i - 1] + nums[i] >= nums[i]) {
      mss[i] = mss[i - 1] + nums[i];
    } else {
      p = i;
    }

    if (mss[i] > maxsum) {
      maxsum = mss[i];
      start = p;
      end = i;
    }
  }

  return {maxsum, start, end};
}

int main() {
  int k;
  std::cin >> k;
  std::vector<int> nums(k);
  for (auto &num : nums) {
    std::cin >> num;
  }

  auto [maxsum, start, end] = SolveMSS(nums);

  if (maxsum >= 0) {
    std::cout << maxsum << " " << nums[start] << " " << nums[end] << std::endl;
  } else {
    std::cout << 0 << " " << nums.front() << " " << nums.back() << std::endl;
  }

  return 0;
}