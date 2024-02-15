#pragma once

#include <memory>

// TODO(zhm): implement this
template<typename T>
class BST
{
public:
private:
  T val_;
  std::unique_ptr<BST<T>> left_;
  std::unique_ptr<BST<T>> right_;
};