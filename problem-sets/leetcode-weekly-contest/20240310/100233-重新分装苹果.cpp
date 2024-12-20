#include <numeric>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumBoxes(std::vector<int>& apple, std::vector<int>& capacity) {
        int sum = std::accumulate(apple.begin(), apple.end(), 0);
        std::sort(capacity.begin(), capacity.end(), std::greater<>());
        int count = 0;
        while (sum > 0) {
            sum = sum - capacity[count++];
        }
        return count;
    }
};