#pragma once

#include <map>
#include <memory>
#include <stack>

template<typename Key, typename Value>
class BST
{
private:
  class Node
  {
    friend class BST;

  public:
    Node(Key key, Value val, int size)
      : key_(std::move(key))
      , val_(std::make_shared<Value>(std::move(val)))
      , left_(nullptr)
      , right_(nullptr)
      , size_(size)
    {}

  private:
    const Key key_;
    std::shared_ptr<Value> val_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
    int size_;
  };

  std::shared_ptr<Node> root_;

  class BSTIterator
  {
  public:
    explicit BSTIterator(std::shared_ptr<Node> root)
    {
      pushAll(root);
    }

    bool hasNext() const
    {
      return !stack_.empty();
    }

    std::shared_ptr<Value> next()
    {
      auto tmpNode = stack_.top();
      stack_.pop();
      pushAll(tmpNode->right_);
      return tmpNode->val_;
    }

  private:
    void pushAll(std::shared_ptr<Node> node)
    {
      while (node != nullptr) {
        stack_.push(node);
        node = node->left_;
      }
    }

    std::stack<std::shared_ptr<Node>> stack_;
  };

public:
  /**
   * @brief an empty symbol table.
   */
  BST() = default;

  /**
   * @brief true if this symbol table is empty.
   * @return true if this symbol table is empty; false otherwise
   */
  bool isEmpty() const
  {
    return size() == 0;
  }

  /**
   * @brief the number of key-value pairs in this symbol table.
   * @return the number of key-value pairs in this symbol table
   */
  int size() const
  {
    return size(root_);
  }

  /**
   * Does this symbol table contain the given key?
   *
   * @param  key the key
   * @return `true` if this symbol table contains {@code key} and
   *         `false` otherwise
   */
  bool contains(const Key &key) const
  {
    return get(key) != nullptr;
  }

  /**
   * @brief the value associated with the given key.
   *
   * @param  key the key
   * @return the value associated with the given key if the key is in the symbol table
   *         and `nullptr` if the key is not in the symbol table
   */
  std::shared_ptr<Value> get(const Key &key) const
  {
    return get(root_, key);
  }

  /**
   * @brief the specified key-value pair into the symbol table, overwriting the old
   * value with the new value if the symbol table already contains the specified key.
   *
   * @param  key the key
   * @param  val the value
   */
  void put(const Key &key, const Value &val)
  {
    root_ = put(root_, key, val);
  }

  /**
   * @brief the smallest key and associated value from the symbol table.
   */
  void deleteMin()
  {
    root_ = deleteMin(root_);
  }

  /**
   * @brief the largest key and associated value from the symbol table.
   */
  void deleteMax()
  {
    root_ = deleteMax(root_);
  }

  /**
   * @brief the specified key and its associated value from this symbol table
   * (if the key is in this symbol table).
   *
   * @param  key the key
   */
  void remove(const Key &key)
  {
    root_ = remove(root_, key);
  }

  /**
   * @brief the smallest key in the symbol table.
   *
   * @return the smallest key in the symbol table
   */
  Key min() const
  {
    return min(root_)->key_;
  }

  /**
   * @brief the largest key in the symbol table.
   *
   * @return the largest key in the symbol table
   */
  Key max() const
  {
    return max(root_)->key_;
  }

  BSTIterator iterator() const
  {
    return BSTIterator(root_);
  }

  /**
   * @brief true if right linear, otherwise false
   * 
   * @return true right linear
   * @return false otherwise
   */
  bool rightLinear()
  {
    return rightLinear(root_);
  }

  /**
   * @brief true if left linear, otherwise false
   * 
   * @return true left linear
   * @return false otherwise
   */
  bool leftLinear()
  {
    return leftLinear(root_);
  }

private:
  std::shared_ptr<Node> put(std::shared_ptr<Node> x, const Key &key, const Value &val)
  {
    if (x == nullptr) {
      return std::make_shared<Node>(key, val, 1);
    }

    if (key < x->key_)
      x->left_ = put(x->left_, key, val);
    else if (key > x->key_)
      x->right_ = put(x->right_, key, val);
    else
      x->val_ = std::make_shared<Value>(val);
    x->size_ = 1 + size(x->left_) + size(x->right_);
    return x;
  }

  // return number of key-value pairs in BST rooted at x
  int size(std::shared_ptr<Node> x) const
  {
    if (x == nullptr)
      return 0;
    return x->size_;
  }

  std::shared_ptr<Value> get(std::shared_ptr<Node> x, const Key &key) const
  {
    if (x == nullptr)
      return nullptr;

    if (key < x->key_)
      return get(x->left_, key);

    if (key > x->key_)
      return get(x->right_, key);

    return x->val_;
  }

  std::shared_ptr<Node> deleteMin(std::shared_ptr<Node> x)
  {
    if (x->left_ == nullptr)
      return x->right_;
    x->left_ = deleteMin(x->left_);
    x->size_ = size(x->left_) + size(x->right_) + 1;
    return x;
  }

  std::shared_ptr<Node> deleteMax(std::shared_ptr<Node> x)
  {
    if (x->right_ == nullptr)
      return x->left_;
    x->right_ = deleteMax(x->right_);
    x->size_  = size(x->left_) + size(x->right_) + 1;
    return x;
  }

  std::shared_ptr<Node> remove(std::shared_ptr<Node> x, const Key &key)
  {
    if (x == nullptr)
      return nullptr;

    if (key < x->key_)
      x->left_ = remove(x->left_, key);
    else if (key > x->key_)
      x->right_ = remove(x->right_, key);
    else {
      if (x->right_ == nullptr)
        return x->left_;
      if (x->left_ == nullptr)
        return x->right_;
      std::shared_ptr<Node> t = x;
      x                       = min(t->right_);
      x->right_               = deleteMin(t->right_);
      x->left_                = t->left_;
    }
    x->size = size(x->left_) + size(x->right_) + 1;
    return x;
  }

  std::shared_ptr<Node> min(std::shared_ptr<Node> x) const
  {
    if (x->left_ == nullptr)
      return x;
    return min(x->left_);
  }

  std::shared_ptr<Node> max(std::shared_ptr<Node> x) const
  {
    if (x->right_ == nullptr)
      return x;
    return max(x->right_);
  }

  bool rightLinear(std::shared_ptr<Node> x) const
  {
    if (x == nullptr)
      return true;
    return x->left_ == nullptr && rightLinear(x->right_);
  }


  bool leftLinear(std::shared_ptr<Node> x) const
  {
    if (x == nullptr)
      return true;
    return x->right_ == nullptr && leftLinear(x->left_);
  }
};