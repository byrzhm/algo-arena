#include <algorithm>
#include <vector>
using std::vector;
namespace ranges = std::ranges;

/**
 * std::ranges::sort -> https://en.cppreference.com/w/cpp/algorithm/ranges/sort
 * std::ranges::less -> https://en.cppreference.com/w/cpp/utility/functional/ranges/less
 * std::identity -> https://en.cppreference.com/w/cpp/utility/functional/identity
 */

// clang-format off
class Solution {
public:
  vector<vector<int>> sortTheStudents(vector<vector<int>> &score, int k) {
    ranges::sort(score, {}, [&](auto &row){ return -row[k]; });
    return score;
  }
};
// clang-format on
