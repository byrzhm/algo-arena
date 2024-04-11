#include <bits/stdc++.h>

#define MAX_ITEM_NUM 101
#define MAX_BAG_SIZE 1001

struct Item {
  int size;
  int value;
  explicit Item(int _size = 0, int _value = 0)
    : size(_size), value(_value) {}
};

struct JumpPoint {
  int capacity;
  int total_value;
  explicit JumpPoint(int _capacity = 0, int _total_value = 0)
    : capacity(_capacity), total_value(_total_value) {}
  bool operator<(const JumpPoint &other) const {
    return capacity < other.capacity;
  }
};

std::vector<Item> items(1);
std::vector<JumpPoint> jump_point_list;
int bag_size, item_number;


void GetInput() {
  std::cin >> bag_size >> item_number;
  for (int i = 0; i < item_number; i++) {
    int item_size, item_value;
    std::cin >> item_size >> item_value;
    items.emplace_back(item_size, item_value);
  }
}

void PrintMergeResult(const std::vector<JumpPoint> &left, const std::vector<JumpPoint> &right, const std::list<JumpPoint> &result) {
  // static int times = 0;
  // std::stringstream sstr;
  // sstr << ++times << ":\n";
  // sstr << "left: ";
  // for (auto &point : left) {
  //   sstr << "(" << point.capacity << ',' << point.total_value << ")  ";
  // }
  // sstr << "\nright: ";
  // for (auto &point : right) {
  //   sstr << "(" << point.capacity << ',' << point.total_value << ")  ";
  // }
  // sstr << "\nresult: ";
  // for (auto &point : result) {
  //   sstr << "(" << point.capacity << ',' << point.total_value << ")  ";
  // }
  // std::cout << sstr.str() << std::endl;
}

std::vector<JumpPoint> Merge(const std::vector<JumpPoint> &left, const std::vector<JumpPoint> &right) {
  std::list<JumpPoint> list;
  int lidx = 0;
  int ridx = 0;

  while (lidx < left.size() && ridx < right.size()) {
    if (left[lidx].capacity < right[ridx].capacity) {
      list.emplace_back(left[lidx++]);
    } else if (left[lidx].capacity > right[ridx].capacity) {
      list.emplace_back(right[ridx++]);
    } else {
      list.emplace_back((left[lidx].total_value > right[ridx].total_value ? left[lidx] : right[ridx]));
      ++lidx;
      ++ridx;
    }
  }

  while (lidx < left.size()) {
    list.emplace_back(left[lidx++]);
  }

  while (ridx < right.size()) {
    list.emplace_back(right[ridx++]);
  }

  auto it = list.begin();
  while (it != list.end()) {
    auto next_it = std::next(it);

    if (next_it != list.end() && next_it->total_value < it->total_value) {
      list.erase(next_it);
    } else {
      ++it;
    }
  }

  PrintMergeResult(left, right, list);

  return std::vector<JumpPoint>{list.begin(), list.end()};
}

void Knapsack() {
  jump_point_list.emplace_back(0, 0);
  for (int i = 1; i <= item_number; i++) {
    auto temp_jump_point_list = std::vector<JumpPoint>{jump_point_list};

    for (auto &jump_point : temp_jump_point_list) {
      jump_point.capacity += items[i].size;
      jump_point.total_value += items[i].value;
    }

    jump_point_list = Merge(jump_point_list, temp_jump_point_list);
  }
}

void OutputAnswer() {
  auto it = std::lower_bound(jump_point_list.begin(), jump_point_list.end(), JumpPoint(bag_size, 0));
  if (it->capacity != bag_size) {
    it = std::prev(it);
    std::cout << it->total_value << std::endl;
  } else {
    std::cout << it->total_value << std::endl;
  }
}

void ShowJumpList() {
  // for (const auto &point : jump_point_list) {
  //   std::cout << point.capacity << ", " << point.total_value << "\n";
  // }
  // std::cout << std::endl;
}

int main() {
  GetInput();
  Knapsack();
  OutputAnswer();
  ShowJumpList();
}