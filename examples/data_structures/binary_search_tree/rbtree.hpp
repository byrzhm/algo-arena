#pragma once

#include <memory>

// TODO(zhm): implement this
template<typename T>
class RBTree
{
public:
private:
  enum class Color
  {
    RED,
    BLACK
  };

  T val_;
  Color color_;
  std::unique_ptr<RBTree<T>> left_;
  std::unique_ptr<RBTree<T>> right_;
};