#include <gtest/gtest.h>
#include <random>

#include "bst.hpp"
#include "rbtree.hpp"

TEST(BSTTest, basic)
{
  BST<int, int> tree;

  // put
  for (int i = 0; i < 8; ++i) {
    tree.put(i, i);
  }

  // contains
  for (int i = 0; i < 8; ++i) {
    EXPECT_TRUE(tree.contains(i)) << "at index " << i << '\n';
  }
  EXPECT_FALSE(tree.contains(88));
  EXPECT_FALSE(tree.contains(-88));

  // get
  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(*tree.get(i), i);
  }
  EXPECT_EQ(tree.get(88), nullptr);
  EXPECT_EQ(tree.get(-88), nullptr);

  EXPECT_EQ(tree.size(), 8);

  // deleteMin/deleteMax
  tree.deleteMin();
  EXPECT_EQ(tree.get(0), nullptr);
  for (int i = 1; i < 8; ++i) {
    EXPECT_EQ(*tree.get(i), i);
  }
  EXPECT_EQ(tree.size(), 7);

  tree.deleteMax();
  EXPECT_EQ(tree.get(0), nullptr);
  EXPECT_EQ(tree.get(7), nullptr);
  for (int i = 1; i <= 6; ++i) {
    EXPECT_EQ(*tree.get(i), i);
  }

  EXPECT_EQ(tree.size(), 6);

  for (int i = 1; i <= 6; ++i) {
    tree.remove(i);
  }
  EXPECT_TRUE(tree.isEmpty());
}

TEST(BSTTest, randomPut)
{
  BST<int, int> tree;
  std::vector<int> input;
  input.reserve(10);
  for (int i = 0; i < 10; ++i) {
    input.emplace_back(i);
  }

  std::shuffle(input.begin(), input.end(), std::mt19937(std::random_device()()));

  for (auto num : input) {
    tree.put(num, num);
  }

  EXPECT_EQ(tree.size(), 10);
  EXPECT_EQ(tree.min(), 0);
  EXPECT_EQ(tree.max(), 9);

  int num = 0;
  for (auto it = tree.iterator(); it.hasNext();) {
    auto val = *it.next();
    EXPECT_EQ(val, num++);
  }
}

TEST(BSTTest, shapeTest)
{
  BST<int, int> tree;

  for (int i = 0; i < 10; ++i) {
    tree.put(i, i);
  }

  EXPECT_TRUE(tree.rightLinear());
  EXPECT_EQ(tree.height(), 9);
}

TEST(RBTreeTest, basic)
{
  RBTree<int, int> tree;

  // put
  for (int i = 0; i < 8; ++i) {
    tree.put(i, i);
  }

  // contains
  for (int i = 0; i < 8; ++i) {
    EXPECT_TRUE(tree.contains(i)) << "at index " << i << '\n';
  }
  EXPECT_FALSE(tree.contains(88));
  EXPECT_FALSE(tree.contains(-88));

  // get
  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(*tree.get(i), i);
  }
  EXPECT_EQ(tree.get(88), nullptr);
  EXPECT_EQ(tree.get(-88), nullptr);

  EXPECT_EQ(tree.size(), 8);
}

TEST(RBTree, randomPut)
{
  RBTree<int, int> tree;
  std::vector<int> input;
  input.reserve(10);
  for (int i = 0; i < 10; ++i) {
    input.emplace_back(i);
  }

  std::shuffle(input.begin(), input.end(), std::mt19937(std::random_device()()));

  for (auto num : input) {
    tree.put(num, num);
  }

  EXPECT_EQ(tree.size(), 10);
  EXPECT_EQ(tree.min(), 0);
  EXPECT_EQ(tree.max(), 9);

  EXPECT_TRUE(tree.isBST()) << "not a BST\n";
  EXPECT_TRUE(tree.is23()) << "not a 2-3 tree\n";
  EXPECT_TRUE(tree.isBalanced()) << "not a balanced tree\n";
}

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}