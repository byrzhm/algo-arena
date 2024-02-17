#pragma once

#include "bst.hpp"
#include <memory>

// TODO(zhm): implement this
template<typename Key, typename Value>
class RBTree
{
private:
  enum class Color : bool
  {
    RED,
    BLACK
  };

  class Node
  {
    friend class RBTree;

  public:
    Node(Key key, Value val, Color color)
      : key_(std::move(key))
      , val_(std::make_shared<Value>(std::move(val)))
      , left_(nullptr)
      , right_(nullptr)
      , color_(color)
    {}

  private:
    Key key_;
    std::shared_ptr<Value> val_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
    Color color_;
  };

  std::shared_ptr<Node> root_;  // root of the BST
  int n_{};                     // number of the key-value pairs in BST

public:
  RBTree()
    : root_(nullptr)
  {}

  // return number of key-value pairs in symbol table
  int size()
  {
    return n_;
  }

  // is the symbol table empty?
  bool isEmpty()
  {
    return n_ == 0;
  }

  // height of tree (1-node tree has height 0)
  int height() { return height(root_); }

  // return the smallest key; null if no such key
  Key min() { return min(root_); }

  // return the largest key; null if no such key
  Key max() { return max(root_); }

  // return value associated with the given key, or null if no such key exists
  std::shared_ptr<Value> get(const Key &key) const
  {
    return get(root_, key);
  }

  // is there a key-value pair in the symbol table with the given key?
  bool contains(const Key &key) const
  {
    return get(key) != nullptr;
  }

  // red-black tree insertion
  void put(const Key &key, const Value &val)
  {
    root_         = insert(root_, key, val);
    root_->color_ = Color::BLACK;
  }

private:
  std::shared_ptr<Value> get(std::shared_ptr<Node> x, const Key &key) const
  {
    while (x != nullptr) {
      if (key < x->key_)
        x = x->left_;
      else if (key > x->key_)
        x = x->right_;
      else
        return x->val_;
    }
    return nullptr;
  }

  std::shared_ptr<Node> insert(std::shared_ptr<Node> h, const Key &key, const Value &val)
  {
    if (h == nullptr) {
      ++n_;
      return std::make_shared<Node>(key, val, Color::RED);
    }
    if (key < h->key_)
      h->left_ = insert(h->left_, key, val);
    else if (key > h->key_)
      h->right_ = insert(h->right_, key, val);
    else
      h->val_ = std::make_shared<Value>(val);

    if (isRed(h->right_) && !isRed(h->left_))
      h = rotateLeft(h);
    if (isRed(h->left_) && isRed(h->left_->left_))
      h = rotateRight(h);
    if (isRed(h->left_) && isRed(h->right_))
      flipColors(h);

    return h;
  }

  std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> h)
  {
    std::shared_ptr<Node> x = h->left_;
    h->left_                = x->right_;
    x->right_               = h;
    x->color_               = h->color_;
    h->color_               = Color::RED;
    return x;
  }

  std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> h)
  {
    std::shared_ptr<Node> x = h->right_;
    h->right_               = x->left_;
    x->left_                = h;
    x->color_               = h->color_;
    h->color_               = Color::RED;
    return x;
  }

  void flipColors(std::shared_ptr<Node> h)
  {
    h->color_        = Color::RED;
    h->left_->color_ = h->right_->color_ = Color::BLACK;
  }

  bool isRed(std::shared_ptr<Node> x)
  {
    if (x == nullptr)
      return false;
    return x->color_ == Color::RED;
  }


public:
  /***************************************************************************
   *  Utility functions.
   ***************************************************************************/
  int height(std::shared_ptr<Node> x)
  {
    if (x == nullptr)
      return -1;
    return 1 + std::max(height(x->left_), height(x->right_));
  }


  Key min(std::shared_ptr<Node> x)
  {
    Key key;
    while (x != nullptr) {
      key = x->key_;
      x   = x->left_;
    }
    return key;
  }

  Key max(std::shared_ptr<Node> x)
  {
    Key key;
    while (x != nullptr) {
      key = x->key_;
      x   = x->right_;
    }
    return key;
  }

  /***************************************************************************
   *  Check integrity of red-black tree data structure.
   ***************************************************************************/

  // does this binary tree satisfy symmetric order?
  // Note: this test also ensures that data structure is a binary tree since order is strict
  bool isBST()
  {
    return isBST(root_, nullptr, nullptr);
  }

  // is the tree rooted at x a BST with all keys strictly between min and max
  // Credit: Bob Dondero's elegant solution
  bool isBST(std::shared_ptr<Node> x, std::unique_ptr<Key> min, std::unique_ptr<Key> max)
  {
    if (x == nullptr)
      return true;
    if (min != nullptr && x->key_ <= *min)
      return false;
    if (max != nullptr && x->key_ >= *max)
      return false;

    bool leftIsBST  = isBST(x->left_, std::move(min), std::make_unique<Key>(x->key_));
    bool rightIsBST = isBST(x->right_, std::make_unique<Key>(x->key_), std::move(max));
    return leftIsBST && rightIsBST;
  }

  // Does the tree have no red right links, and at most one (left)
  // red links in a row on any path?
  bool is23() { return is23(root_); }
  bool is23(std::shared_ptr<Node> x)
  {
    if (x == nullptr)
      return true;
    if (isRed(x->right_))
      return false;
    if (x != root_ && isRed(x) && isRed(x->left_))
      return false;
    return is23(x->left_) && is23(x->right_);
  }

  // do all paths from root to leaf have same number of black edges?
  bool isBalanced()
  {
    int black               = 0;  // number of black links on path from root to min
    std::shared_ptr<Node> x = root_;
    while (x != nullptr) {
      if (!isRed(x))
        black++;
      x = x->left_;
    }
    return isBalanced(root_, black);
  }

  // does every path from the root to a leaf have the given number of black links?
  bool isBalanced(std::shared_ptr<Node> x, int black)
  {
    if (x == nullptr)
      return black == 0;
    if (!isRed(x))
      black--;
    return isBalanced(x->left_, black) && isBalanced(x->right_, black);
  }
};