#include <iostream>
#include <set>

#define MAXN 10000

int height[MAXN + 1];
int diff[MAXN + 1];
std::set<std::pair<int, int> > seen;
int n, m_idx, max_height;

int main() {
    int lineno;
    std::cin >> n >> m_idx >> max_height >> lineno;
    height[0] = max_height;
    // height[m_idx] = max_height;

    while ((lineno--) != 0) {
        // cow_a sees cow_b
        // cow_between_ab < height[cow_a] <= height[cow_b]
        int cow_a, cow_b;
        std::cin >> cow_a >> cow_b;

        std::pair<int, int> pair = std::make_pair(cow_a, cow_b);

        if (seen.find(pair) != seen.end()) {
            continue;
        }
        seen.insert(pair);

        int low = std::min(cow_a, cow_b) + 1;
        int high = std::max(cow_a, cow_b) - 1;

        if (low <= high) {
            diff[low] += -1;
            diff[high + 1] += 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        height[i] = diff[i] + height[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        // std::cout << height[i] << (i == n ? "\n" : " ");
        std::cout << height[i] << "\n";
    }
    return 0;
}